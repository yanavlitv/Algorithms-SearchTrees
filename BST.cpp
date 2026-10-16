#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) {
        key = k;
        left = nullptr;
        right = nullptr;
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
        if (x == (*cur).key) return;
        if (x < (*cur).key) {
            if ((*cur).left == nullptr) {
                (*cur).left = new Node(x);
                return;
            }
            cur = (*cur).left;
        } else {
            if ((*cur).right == nullptr) {
                (*cur).right = new Node(x);
                return;
            }
            cur = (*cur).right;
        }
    }
}

bool exists(int x) {
    Node* cur = t.root;
    while (cur != nullptr) {
        if (x == (*cur).key) return true;
        if (x < (*cur).key) cur = (*cur).left;
        else cur = (*cur).right;
    }
    return false;
}

Node* findMin(Node* node) {
    while ((*node).left != nullptr) {
        node = (*node).left;
    }
    return node;
}

Node* deleteNode(Node* node, int x) {
    if (node == nullptr) return nullptr;
    
    if (x < (*node).key) {
        (*node).left = deleteNode((*node).left, x);
    } else if (x > (*node).key) {
        (*node).right = deleteNode((*node).right, x);
    } else {
        if ((*node).left == nullptr) {
            Node* tmp = (*node).right;
            delete node;
            return tmp;
        }
        if ((*node).right == nullptr) {
            Node* tmp = (*node).left;
            delete node;
            return tmp;
        }
        Node* succ = findMin((*node).right);
        (*node).key = (*succ).key;
        (*node).right = deleteNode((*node).right, (*succ).key);
    }
    return node;
}

void del(int x) {
    t.root = deleteNode(t.root, x);
}

int height(Node* node) {
    if (node == nullptr) return 0;
    int lh = height((*node).left);
    int rh = height((*node).right);
    if (lh > rh) return 1 + lh;
    return 1 + rh;
}

void preorder(Node* node, vector<int>& out) {
    if (node == nullptr) return;
    out.push_back((*node).key);
    preorder((*node).left, out);
    preorder((*node).right, out);
}

void destroy(Node* node) {
    if (node == nullptr) return;
    destroy((*node).left);
    destroy((*node).right);
    delete node;
}

int main() {
    int Q;
    cin >> Q;
    
    for (int i = 0; i < Q; i++) {
        string cmd;
        cin >> cmd;
        
        if (cmd == "add") {
            int x; cin >> x;
            add(x);                   
        }
        if (cmd == "del") {
            int x; cin >> x;
            del(x);                   
        } 
        if (cmd == "exists") {
            int x; cin >> x;
            if (exists(x)) cout << "YES\n";
            else cout << "NO\n";
        } 
        if (cmd == "height") {
            cout << height(t.root) << "\n";
        }
        if (cmd == "print") {
            vector<int> keys;
            preorder(t.root, keys);
            if (keys.empty()) {
                cout << "Empty\n";
            } else {
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