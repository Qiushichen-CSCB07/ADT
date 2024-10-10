#include "utils.h"

int maxNum(int a, int b) {
    if (a >= b) {
        return a;
    }
    return b;
}

int get_size(Node *node) {
    if (node == NULL) {
        return 0;
    } else {
        return node->size;
    }
}

int get_height(Node* node) {
    if (node == NULL) {
        return 0;
    } else {
        return node->height;
    }
}

void update_height(Node* node) {
    if (node != NULL) {
        node->height = maxNum(get_height(node->left), get_height(node->right)) + 1;
    }
}

void update_size(Node* node) {
    if (node != NULL) {
        node->size = get_size(node->left) + get_size(node->right) + 1;
    }
}

Node* left_left(Node* v) {
    Node* x = v->left;
    v->left = x->right;
    x->right = v;
    update_height(v);
    update_size(v);
    update_height(x);
    update_size(x);
    return x;
}

Node* right_right(Node* v) {
    Node* x = v->right;
    v->right = x->left;
    x->left = v;
    update_height(v);
    update_size(v);
    update_height(x);
    update_size(x);
    return x;
}

Node* left_right(Node* v) {
    v->left = right_right(v->left);
    v = left_left(v);
    return v;
}

Node* right_left(Node* v) {
    v->right = left_left(v->right);
    v = right_right(v);
    return v;
}

Node* rebalance(Node* node) {
    if (node == NULL) return node;
    if (get_height(node->left) - get_height(node->right) > 1) {
        if (get_height(node->left->left) >= get_height(node->left->right)) {
            node = left_left(node);
        } else {
            node = left_right(node);
        }
    } else if (get_height(node->right) - get_height(node->left) > 1) {
        if (get_height(node->right->right) >= get_height(node->right->left)) {
            node = right_right(node);
        } else {
            node = right_left(node);
        }
    }
    update_height(node);
    update_size(node);
    return node;
}
