#include "avl_tree.h"
#include "utils.h"

Node* create(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->height = 1;
    node->size = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* Insert(Node* node, int key) {
    if (node == NULL) {
        Node* new_node = create(key);
        return new_node;
    } else if (key < node->key) {
        node->left = Insert(node->left, key);
    } else if (key > node->key) {
        node->right = Insert(node->right, key);
    } else {
        printf("cannot insert value that is already in AVL tree.\n");
    }
    node = rebalance(node);
    return node;
}

Node* search(Node* node, int key) {
    if (node == NULL || node->key == key) {
        return node;
    } else if (key < node->key) {
        return search(node->left, key);
    } else {
        return search(node->right, key);
    }
}

Node* successor(Node* node) {
    node = node->right;
    if (node == NULL) {
        return NULL;
    }
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

Node* del(Node* node, int key) {
    Node* target = search(node, key);
    if (target == NULL) {
        printf("delete failed.\n");
        return node;
    }

    if (key < node->key) {
        node->left = del(node->left, key);
    } else if (key > node->key) {
        node->right = del(node->right, key);
    } else if (key == node->key) {
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        } else if (node->right == NULL) {
            Node* tmp = node;
            node = node->left;
            free(tmp);
        } else if (node->left == NULL) {
            Node* tmp = node;
            node = node->right;
            free(tmp);
        } else {
            Node* succ_node = successor(node);
            node->key = succ_node->key;
            node->right = del(node->right, succ_node->key);
        }
    }
    node = rebalance(node);
    return node;
}

int get_rank(Node* node, int key) {
    if (node == NULL) {
        return NOTIN;
    }
    if (key < node->key) {
        return get_rank(node->left, key);
    } else if (key > node->key) {
        int right_rank = get_rank(node->right, key);
        if (right_rank == NOTIN) {
            return NOTIN;
        }
        return 1 + get_size(node->left) + right_rank;
    } else {
        return 1 + get_size(node->left);
    }
}

Node* findRank(Node* node, int rank) {
    if (node == NULL) {
        return NULL;
    }
    int leftSize = get_size(node->left);
    if (rank == leftSize + 1) {
        return node;
    } else if (rank <= leftSize) {
        return findRank(node->left, rank);
    } else {
        return findRank(node->right, rank - leftSize - 1);
    }
}

void pre_order(Node* node) {
    if (node) {
        printf("[ %d ]  height:%d  size:%d\n", node->key, node->height, node->size);
        pre_order(node->left);
        pre_order(node->right);
    }
}

void in_order(Node* node) {
    if (node) {
        in_order(node->left);
        printf("[ %d ]  height:%d  size:%d\n", node->key, node->height, node->size);
        in_order(node->right);
    }
}

void post_order(Node* node) {
    if (node) {
        post_order(node->left);
        post_order(node->right);
        printf("[ %d ]  height:%d  size:%d\n", node->key, node->height, node->size);
    }
}

Node* join(Node* L, int key, Node* R) {
    int L_height = get_height(L);
    int R_height = get_height(R);

    printf("join: L_height = %d, key = %d, R_height = %d\n", L_height, key, R_height);

    if ((L_height - R_height) > 1) {
        L->right = join(L->right, key, R);
        L->right = rebalance(L->right);
        L = rebalance(L);
        return L;
    } else if ((R_height - L_height) > 1) {
        R->left = join(L, key, R->left);
        R->left = rebalance(R->left);
        R = rebalance(R);
        return R;
    } else {
        Node* nodeK = create(key);
        nodeK->left = L;
        nodeK->right = R;
        nodeK = rebalance(nodeK);

        printf("join result: nodeK->key = %d\n", nodeK->key);

        return nodeK;
    }
}

SplitResult split(Node* T, int k) {
    SplitResult result;
    result.left = NULL;
    result.right = NULL;
    if (T == NULL) {
        return result;
    }

    printf("split: T->key = %d, k = %d\n", T->key, k);

    if (k == T->key) {
        result.left = T->left;
        result.right = T->right;
        return result;
    } else if (k < T->key) {
        result = split(T->left, k);
        result.right = join(result.right, T->key, T->right);
    } else if (k > T->key) {
        result = split(T->right, k);
        result.left = join(T->left, T->key, result.left);
    }

    printf("split result: left = %p, right = %p\n", result.left, result.right);

    return result;
}

Node* tree_union(Node* T1, Node* T2) {
    if (T1 == NULL) return T2;
    if (T2 == NULL) return T1;

    printf("tree_union: T1->key = %d, T2->key = %d\n", T1->key, T2->key);
    
    SplitResult splitResult = split(T1, T2->key);
    Node* leftUnion = tree_union(splitResult.left, T2->left);
    Node* rightUnion = tree_union(splitResult.right, T2->right);

    Node* result = join(leftUnion, T2->key, rightUnion);

    printf("tree_union result: root->key = %d\n", result->key);

    return result;
}

void delete_AVL(Node* node) {
    if (node != NULL) {
        delete_AVL(node->left);
        delete_AVL(node->right);
        free(node);
    }
}
