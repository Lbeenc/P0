
#ifndef TREE_H
#define TREE_H

#include "node.h"

typedef struct Tree {
    Node *root;
} Tree;

// Create/destroy
void tree_init(Tree *t);
void tree_free(Tree *t);

// Insert/find a node with given frequency (creates if not present)
Node *tree_get_or_insert(Tree *t, int freq);

// Append a string to a node (takes ownership by duplicating the string)
void node_append_item(Node *n, const char *s);

// Printing (three traversals) — writes to FILE*
void print_preorder(Node *root, FILE *out, int depth);
void print_inorder(Node *root, FILE *out, int depth);
void print_postorder(Node *root, FILE *out, int depth);

#endif // TREE_H
