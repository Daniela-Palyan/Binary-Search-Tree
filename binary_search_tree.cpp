#include <iostream>

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int value) {
        if (!node) return new Node(value);
        if (value < node->value)
            node->left = insert(node->left, value);
        else if (value > node->value)
            node->right = insert(node->right, value);
        return node;
    }

    bool find(Node* node, int value) {
        if (!node) return false;
        if (node->value == value) return true;
        if (value < node->value)
            return find(node->left, value);
        else
            return find(node->right, value);
    }

    Node* find_min(Node* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    Node* find_max(Node* node) {
        while (node && node->right)
            node = node->right;
        return node;
    }

    int get_hight(Node* node) {
        if (!node) return 0;
        int left = get_hight(node->left);
        int right = get_hight(node->right);
        return 1 + (left > right ? left : right);
    }


    Node* delete_node(Node* node, int value) {
        if (!node) return nullptr;
        if (value < node->value)
            node->left = delete_node(node->left, value);
        else if (value > node->value)
            node->right = delete_node(node->right, value);
        else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            } else if (!node->left) {
                Node* tmp = node->right;
                delete node;
                return tmp;
            } else if (!node->right) {
                Node* tmp = node->left;
                delete node;
                return tmp;
            } else {
                Node* tmp = find_min(node->right);
                node->value = tmp->value;
                node->right = delete_node(node->right, tmp->value);
            }
        }
        return node;
    }

    void delete_all(Node* node) {
        if (!node) return;
        delete_all(node->left);
        delete_all(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { delete_all(root); }
    void insert(int value) { root = insert(root, value); }
    bool find(int value) { return find(root, value); }
    void delete_value(int value) { root = delete_node(root, value); }
    int hight() { return get_hight(root); }
};