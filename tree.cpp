#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "tree.h"

static Node* insertByFreq(Node* root, int freq, const std::string& word) {
    if (!root) {
        Node* n = new Node(freq);
        n->items.push_back(word);
        return n;
    }
    if (freq < root->freq) {
        root->left = insertByFreq(root->left, freq, word);
    } else if (freq > root->freq) {
        root->right = insertByFreq(root->right, freq, word);
    } else {
        root->items.push_back(word);
    }
    return root;
}

Node* buildTree(const std::vector<std::string>& unique_order,
                const std::unordered_map<std::string,int>& freq) {
    Node* root = nullptr;
    for (const std::string& w : unique_order) {
        auto it = freq.find(w);
        if (it == freq.end()) continue;
        root = insertByFreq(root, it->second, w);
    }
    return root;
}

static void printOne(Node* node, std::ostream& out, int depth) {
    if (!node) return;
    out << std::string(depth * 2, ' ');
    out << node->freq << ": ";
    for (size_t i = 0; i < node->items.size(); ++i) {
        if (i) out << ' ';
        out << node->items[i];
    }
    out << '\n';
}

void printPreorder(Node* root, std::ostream& out, int depth) {
    if (!root) return;
    printOne(root, out, depth);
    printPreorder(root->left, out, depth+1);
    printPreorder(root->right, out, depth+1);
}

void printInorder(Node* root, std::ostream& out, int depth) {
    if (!root) return;
    printInorder(root->left, out, depth+1);
    printOne(root, out, depth);
    printInorder(root->right, out, depth+1);
}

void printPostorder(Node* root, std::ostream& out, int depth) {
    if (!root) return;
    printPostorder(root->left, out, depth+1);
    printPostorder(root->right, out, depth+1);
    printOne(root, out, depth);
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}
