#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int key;
    int h;
    Node* left;
    Node* right;
    Node(int k) {
        key = k;
        h = 1;
        left = nullptr;
        right = nullptr;
    }
};

struct Tree {
    Node* root = nullptr;
};

Tree t;

int height(Node* node) {
    if (node == nullptr) return 0;
    return node->h;
}

int balance(Node* node) {
    if (node == nullptr) return 0;
    return height(node->right) - height(node->left);
}

void fixHeight(Node* node) {
    int lh = height(node->left);
    int rh = height(node->right);
    node->h = max(lh, rh) + 1;
}

Node* rotateLeft(Node* a) {
    Node* b = a->right;
    a->right = b->left;
    b->left = a;
    fixHeight(a);
    fixHeight(b);
    return b;
}

Node* rotateRight(Node* a) {
    Node* b = a->left;
    a->left = b->right;
    b->right = a;
    fixHeight(a);
    fixHeight(b);
    return b;
}

Node* rebalance(Node* node) {
    if (node == nullptr) return nullptr;
    fixHeight(node);
    if (balance(node) == 2) {
        if (balance(node->right) < 0) node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    if (balance(node) == -2) {
        if (balance(node->left) > 0) node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    return node;
}

Node* add(Node* node, int x) {
    if (node == nullptr) return new Node(x);
    if (x < node->key) node->left = add(node->left, x);
    else if (x > node->key) node->right = add(node->right, x);
    else return node;
    return rebalance(node);
}

Node* findMin(Node* node) {
    while (node->left != nullptr) node = node->left;
    return node;
}

Node* removeMin(Node* node) {
    if (node->left == nullptr) {
        Node* right = node->right;
        delete node;
        return right;
    }
    node->left = removeMin(node->left);
    return rebalance(node);
}

Node* del(Node* node, int x) {
    if (node == nullptr) return nullptr;
    if (x < node->key) node->left = del(node->left, x);
    else if (x > node->key) node->right = del(node->right, x);
    else {
        Node* left = node->left;
        Node* right = node->right;
        delete node;
        if (right == nullptr) return left;
        Node* minNode = findMin(right);
        minNode->right = removeMin(right);
        minNode->left = left;
        return rebalance(minNode);
    }
    return rebalance(node);
}

bool exists(int x) {
    Node* cur = t.root;
    while (cur != nullptr) {
        if (cur->key == x) return true;
        if (x < cur->key) cur = cur->left;
        else cur = cur->right;
    }
    return false;
}

Node* nextKey(int x) {
    Node* cur = t.root;
    Node* ans = nullptr;
    while (cur != nullptr) {
        if (cur->key >= x) {
            ans = cur;
            cur = cur->left;
        } else cur = cur->right;
    }
    return ans;
}

Node* prevKey(int x) {
    Node* cur = t.root;
    Node* ans = nullptr;
    while (cur != nullptr) {
        if (cur->key <= x) {
            ans = cur;
            cur = cur->right;
        } else cur = cur->left;
    }
    return ans;
}

void preorder(Node* node, vector<int>& out) {
    if (node == nullptr) return;
    out.push_back(node->key);
    preorder(node->left, out);
    preorder(node->right, out);
}

void destroy(Node* node) {
    if (node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

int main() {
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "add") {
            int x;
            cin >> x;
            t.root = add(t.root, x);
        } else if (cmd == "del") {
            int x;
            cin >> x;
            t.root = del(t.root, x);
        } else if (cmd == "exists") {
            int x;
            cin >> x;
            cout << (exists(x) ? "YES" : "NO") << "\n";
        } else if (cmd == "next") {
            int x;
            cin >> x;
            Node* ans = nextKey(x);
            if (ans == nullptr) cout << "None\n";
            else cout << ans->key << "\n";
        } else if (cmd == "prev") {
            int x;
            cin >> x;
            Node* ans = prevKey(x);
            if (ans == nullptr) cout << "None\n";
            else cout << ans->key << "\n";
        } else if (cmd == "root") {
            if (t.root == nullptr) cout << "Empty\n";
            else cout << t.root->key << "\n";
        } else if (cmd == "height") {
            cout << height(t.root) << "\n";
        } else if (cmd == "print") {
            vector<int> keys;
            preorder(t.root, keys);
            if (keys.empty()) cout << "Empty\n";
            else {
                for (int j = 0; j < (int)keys.size(); j++) {
                    if (j > 0) cout << " ";
                    cout << keys[j];
                }
                cout << "\n";
            }
        }
    }
    destroy(t.root);
    return 0;
}
