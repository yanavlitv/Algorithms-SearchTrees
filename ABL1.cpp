#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;
    Node(int k) {
        key = k;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

struct Tree {
    Node* root = nullptr;
};

Tree t;

void add(int x) {
    if (t.root == nullptr) {
        t.root = new Node(x);
        return;
    }

    Node* cur = t.root;

    while (true) {
        if (x == cur->key) return;
        if (x < cur->key) {
            if (cur->left == nullptr) {
                cur->left = new Node(x);
                cur->left->parent = cur;
                return;
            }
            cur = cur->left;
        } else {
            if (cur->right == nullptr) {
                cur->right = new Node(x);
                cur->right->parent = cur;
                return;
            }
            cur = cur->right;
        }
    }
}

Node* findNode(int x) {
    Node* cur = t.root;
    while (cur != nullptr) {
        if (cur->key == x) return cur;
        if (x < cur->key) cur = cur->left;
        else cur = cur->right;
    }

    return nullptr;
}

void leftRotate(Node* a) {
    Node* b = a->right;
    Node* p = a->parent;
    a->right = b->left;
    if (b->left != nullptr) b->left->parent = a;
    b->left = a;
    a->parent = b;
    b->parent = p;
    if (p == nullptr) t.root = b;
    else if (p->left == a) p->left = b;
    else p->right = b;
}

void rightRotate(Node* a) {
    Node* b = a->left;
    Node* p = a->parent;
    a->left = b->right;
    if (b->right != nullptr) b->right->parent = a;
    b->right = a;
    a->parent = b;
    b->parent = p;
    if (p == nullptr) t.root = b;
    else if (p->left == a) p->left = b;
    else p->right = b;
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
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        add(x);
    }

    int M;
    cin >> M;
    for (int i = 0; i < M; i++) {
        string cmd;
        int x;
        cin >> cmd >> x;

        Node* node = findNode(x);

        if (cmd == "left") {
            leftRotate(node);
        } else {
            rightRotate(node);
        }

        vector<int> keys;
        preorder(t.root, keys);

        for (int j = 0; j < (int)keys.size(); j++) {
            if (j > 0) cout << " ";
            cout << keys[j];
        }
        cout << "\n";
    }

    destroy(t.root);
    return 0;
}
