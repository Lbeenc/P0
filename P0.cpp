#include <bits/stdc++.h>
#include "node.h"
#include "tree.h"

using namespace std;

static void exitError(const string& s) {
    cerr << s << "\n";
    exit(1);
}

static bool isAlnumString(const string& s) {
    if (s.empty()) return false;
    for (unsigned char c : s) {
        if (!std::isalnum(c)) return false;
    }
    return true;
}

static vector<string> readTokens(istream& in,
                                 vector<string>& unique_in_order,
                                 unordered_map<string,int>& freq) {
    vector<string> tokens;
    unordered_set<string> seen;

    string w;
    while (in >> w) {
        if (!isAlnumString(w)) {
            cerr << "Warning: skipping invalid token '" << w << "' (letters/digits only).\n";
            continue;
        }
        tokens.push_back(w);
        ++freq[w];
        if (!seen.count(w)) {
            unique_in_order.push_back(w);
            seen.insert(w);
        }
    }
    return tokens;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc > 2) {
        exitError("Too many arguments. Usage: P0 [fileBaseName]");
    }

    string outBase;
    unique_ptr<istream> fileIn;

    if (argc == 1) {
        outBase = "out";
    } else {
        string base = argv[1];
        if (base.find('.') != string::npos) {
            exitError("Do not include an extension on the command line (the .fs25s2 extension is implicit).");
        }
        string filename = base + ".fs25s2";
        fileIn = make_unique<ifstream>(filename);
        if (!*fileIn) {
            exitError("Cannot read input file '" + filename + "'.");
        }
        outBase = base;
    }

    istream& in = (fileIn ? *fileIn : cin);

    vector<string> unique_in_order;
    unordered_map<string,int> freq;
    (void)readTokens(in, unique_in_order, freq);

    if (unique_in_order.empty()) {
        exitError("No valid input tokens to process.");
    }

    Node* root = buildTree(unique_in_order, freq);

    ofstream pre(outBase + ".preorder");
    ofstream ino(outBase + ".inorder");
    ofstream post(outBase + ".postorder");
    if (!pre || !ino || !post) {
        freeTree(root);
        exitError("Failed to open one of the output files for writing.");
    }

    printPreorder(root, pre, 0);
    printInorder(root, ino, 0);
    printPostorder(root, post, 0);

    freeTree(root);
    return 0;
}
