
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"

#define HASH_SIZE 4096

typedef struct Entry {
    char *token;
    int count;
    long first_index;   // order of first appearance
    struct Entry *next; // for hash bucket
} Entry;

static unsigned long djb2(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

static Entry *table[HASH_SIZE] = {0};
static long global_index_counter = 0;
static int validation_enabled = 1; // print warnings for invalid tokens

static int is_valid_token(const char *s) {
    if (!s || !*s) return 0;
    for (const char *p = s; *p; ++p) {
        if (!isalnum((unsigned char)*p)) return 0;
    }
    return 1;
}

static Entry *get_or_add(const char *tok) {
    unsigned long h = djb2(tok) % HASH_SIZE;
    Entry *cur = table[h];
    while (cur) {
        if (strcmp(cur->token, tok) == 0) return cur;
        cur = cur->next;
    }
    // new
    Entry *e = (Entry *)malloc(sizeof(Entry));
    e->token = strdup(tok);
    e->count = 0;
    e->first_index = -1;
    e->next = table[h];
    table[h] = e;
    return e;
}

static void free_table(void) {
    for (int i = 0; i < HASH_SIZE; ++i) {
        Entry *cur = table[i];
        while (cur) {
            Entry *nxt = cur->next;
            free(cur->token);
            free(cur);
            cur = nxt;
        }
        table[i] = NULL;
    }
}

static void collect_entries(Entry ***arr_out, size_t *n_out) {
    size_t cap = 128, n = 0;
    Entry **arr = (Entry **)malloc(cap * sizeof(Entry *));
    for (int i = 0; i < HASH_SIZE; ++i) {
        for (Entry *cur = table[i]; cur; cur = cur->next) {
            if (n == cap) {
                cap *= 2;
                arr = (Entry **)realloc(arr, cap * sizeof(Entry *));
            }
            arr[n++] = cur;
        }
    }
    *arr_out = arr;
    *n_out = n;
}

static int cmp_first_index(const void *a, const void *b) {
    const Entry *ea = *(const Entry * const *)a;
    const Entry *eb = *(const Entry * const *)b;
    if (ea->first_index < eb->first_index) return -1;
    if (ea->first_index > eb->first_index) return 1;
    return 0;
}

int main(int argc, char **argv) {
    // Determine input and basename for outputs
    const char *input_basename = NULL;
    FILE *in = NULL;
    char pathbuf[1024];

    if (argc == 1) {
        // stdin
        in = stdin;
        input_basename = "out";
    } else if (argc == 2) {
        // file with implicit extension .fs25s2
        const char *base = argv[1];
        if (strchr(base, '.')) {
            fprintf(stderr, "ERROR: Do not include an extension. The program appends .fs25s2\n");
            return 1;
        }
        snprintf(pathbuf, sizeof(pathbuf), "%s.fs25s2", base);
        in = fopen(pathbuf, "r");
        if (!in) {
            fprintf(stderr, "ERROR: Cannot open input file '%s'\n", pathbuf);
            return 1;
        }
        input_basename = base;
    } else {
        fprintf(stderr, "USAGE: %s [file]\n", argv[0]);
        return 1;
    }

    // Read tokens (unknown input size)
    char buf[4096];
    while (fscanf(in, "%4095s", buf) == 1) {
        if (!is_valid_token(buf)) {
            if (validation_enabled) {
                fprintf(stderr, "WARNING: Skipping invalid token: '%s'\n", buf);
            }
            continue;
        }
        Entry *e = get_or_add(buf);
        if (e->count == 0) {
            e->first_index = global_index_counter++;
        }
        e->count += 1;
    }

    if (in != stdin && in) fclose(in);

    // Build BST keyed by frequency; populate each node's items in first-appearance order
    Tree t;
    tree_init(&t);

    Entry **all = NULL;
    size_t nall = 0;
    collect_entries(&all, &nall);
    // Sort by first appearance to preserve order inside nodes
    qsort(all, nall, sizeof(Entry *), cmp_first_index);

    for (size_t i = 0; i < nall; ++i) {
        Entry *e = all[i];
        if (e->count <= 0) continue;
        Node *node = tree_get_or_insert(&t, e->count);
        node_append_item(node, e->token);
    }
    free(all);

    // Open output files
    char pre_path[1024], in_path[1024], post_path[1024];
    snprintf(pre_path, sizeof(pre_path), "%s.preorder", input_basename);
    snprintf(in_path,  sizeof(in_path), "%s.inorder",  input_basename);
    snprintf(post_path,sizeof(post_path),"%s.postorder",input_basename);

    FILE *fpre = fopen(pre_path, "w");
    FILE *fin  = fopen(in_path,  "w");
    FILE *fpost= fopen(post_path,"w");

    if (!fpre || !fin || !fpost) {
        fprintf(stderr, "ERROR: Cannot open output files for writing.\n");
        if (fpre) fclose(fpre);
        if (fin) fclose(fin);
        if (fpost) fclose(fpost);
        tree_free(&t);
        free_table();
        return 1;
    }

    print_preorder(t.root, fpre, 0);
    print_inorder(t.root,  fin,  0);
    print_postorder(t.root,fpost,0);

    fclose(fpre); fclose(fin); fclose(fpost);

    // Cleanup
    tree_free(&t);
    free_table();

    return 0;
}
