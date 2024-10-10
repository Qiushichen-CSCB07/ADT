#ifndef UTILS_H
#define UTILS_H

#include "avl_tree.h"

int maxNum(int a, int b);
int get_size(Node* node);
int get_height(Node* node);
void update_height(Node* node);
void update_size(Node* node);
Node* left_left(Node* v);
Node* right_right(Node* v);
Node* left_right(Node* v);
Node* right_left(Node* v);
Node* rebalance(Node* node);

#endif
