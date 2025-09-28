#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

struct Node {
    int freq;
    std::vector<std::string> items;
    Node* left;
    Node* right;
    explicit Node(int f) : freq(f), left(nullptr), right(nullptr) {}
};

#endif // NODE_H
