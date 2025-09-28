
#ifndef NODE_H
#define NODE_H

#include <stdio.h>

typedef struct Node {
    int freq;                 // key: frequency
    char **items;             // strings with this frequency
    int size;                 // number of strings stored
    int capacity;             // capacity of items
    struct Node *left;
    struct Node *right;
} Node;

#endif // NODE_H
