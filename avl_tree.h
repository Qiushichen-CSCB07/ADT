
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>

#define NOTIN -1

typedef struct AVLNode {
    int key;
    int height;
    int size;
    struct AVLNode* left;
    struct AVLNode* right;
} Node;

typedef struct SplitResult {
    Node* left;
    Node* right;
} SplitResult;

Node* create(int key);
Node* Insert(Node* node, int key);
Node* search(Node* node, int key);
Node* del(Node* node, int key);
Node* findRank(Node* node, int rank);
int get_rank(Node* node, int key);
void pre_order(Node* node);
void in_order(Node* node);
void post_order(Node* node);
Node* join(Node* L, int key, Node* R);
SplitResult split(Node* T, int k);
Node* tree_union(Node* T1, Node* T2);
void delete_AVL(Node* node);

#endif
