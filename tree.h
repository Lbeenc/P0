#ifndef TREE_H
#define TREE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <iosfwd>
#include "node.h"

Node* buildTree(const std::vector<std::string>& unique_order,
                const std::unordered_map<std::string,int>& freq);

void printPreorder(Node* root, std::ostream& out, int depth=0);
void printInorder(Node* root, std::ostream& out, int depth=0);
void printPostorder(Node* root, std::ostream& out, int depth=0);

void freeTree(Node* root);

#endif // TREE_H
