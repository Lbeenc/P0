
#include "tree.h"
#include <stdlib.h>
#include <string.h>

static Node *node_new(int freq) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) return NULL;
    n->freq = freq;
    n->items = NULL;
    n->size = 0;
    n->capacity = 0;
    n->left = n->right = NULL;
    return n;
}

static void node_free(Node *n) {
    if (!n) return;
    for (int i = 0; i < n->size; ++i) {
        free(n->items[i]);
    }
    free(n->items);
    free(n);
}

static void node_free_recursive(Node *n) {
    if (!n) return;
    node_free_recursive(n->left);
    node_free_recursive(n->right);
    node_free(n);
}

void tree_init(Tree *t) {
    t->root = NULL;
}

void tree_free(Tree *t) {
    node_free_recursive(t->root);
    t->root = NULL;
}

Node *tree_get_or_insert(Tree *t, int freq) {
    if (!t->root) {
        t->root = node_new(freq);
        return t->root;
    }
    Node *cur = t->root;
    while (1) {
        if (freq == cur->freq) return cur;
        else if (freq < cur->freq) {
            if (!cur->left) {
                cur->left = node_new(freq);
                return cur->left;
            }
            cur = cur->left;
        } else { // freq > cur->freq
            if (!cur->right) {
                cur->right = node_new(freq);
                return cur->right;
            }
            cur = cur->right;
        }
    }
}

void node_append_item(Node *n, const char *s) {
    if (!n) return;
    if (n->size == n->capacity) {
        int newcap = n->capacity == 0 ? 4 : n->capacity * 2;
        char **tmp = (char **)realloc(n->items, newcap * sizeof(char *));
        if (!tmp) return;
        n->items = tmp;
        n->capacity = newcap;
    }
    n->items[n->size++] = strdup(s);
}

static void print_indent(FILE *out, int depth) {
    for (int i = 0; i < depth * 2; ++i) fputc(' ', out);
}

static void print_node_line(Node *n, FILE *out, int depth) {
    print_indent(out, depth);
    fprintf(out, "%d: ", n->freq);
    for (int i = 0; i < n->size; ++i) {
        fprintf(out, "%s", n->items[i]);
        if (i + 1 < n->size) fputc(' ', out);
    }
    fputc('\n', out);
}

void print_preorder(Node *root, FILE *out, int depth) {
    if (!root) return;
    print_node_line(root, out, depth);
    print_preorder(root->left, out, depth + 1);
    print_preorder(root->right, out, depth + 1);
}

void print_inorder(Node *root, FILE *out, int depth) {
    if (!root) return;
    print_inorder(root->left, out, depth + 1);
    print_node_line(root, out, depth);
    print_inorder(root->right, out, depth + 1);
}

void print_postorder(Node *root, FILE *out, int depth) {
    if (!root) return;
    print_postorder(root->left, out, depth + 1);
    print_postorder(root->right, out, depth + 1);
    print_node_line(root, out, depth);
}
