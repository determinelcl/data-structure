//
// Created by determination on 2018/9/10.
//

#include "avl_tree.h"

static int max_AVLT(int num, int another);

static AvlTree singleRotateWithRight(AvlTree k1);

static AvlTree betaIsOrNotRotateWithLeft(AvlTree tree, DataType_AVLT data);

static AvlTree betaIsOrNotRotateWithRight(AvlTree tree, DataType_AVLT data);

AvlTree newAvlTree(void) {
    return NULL;
}

AvlTree makeEmpty_AVLT(AvlTree tree) {
    if (tree) {
        makeEmpty_AVLT(tree->left);
        makeEmpty_AVLT(tree->right);
        free(tree);
    }
    return NULL;
}

Position_AVLT find_AVLT(AvlTree tree, DataType_AVLT data) {
    if (!tree) return NULL;

    Comparable result = COMPARE_WITH(tree->data, data);
    if (result == GT)
        return find_AVLT(tree->left, data);
    else if (result == LT)
        return find_AVLT(tree->right, data);
    else return tree;
}


Position_AVLT findMin_AVLT(AvlTree tree) {
    if (!tree) return NULL;
    else if (!tree->left) return tree;
    else return findMin_AVLT(tree->left);
}


Position_AVLT findMax_AVLT(AvlTree tree) {
    if (tree)
        while (tree->right)
            tree = tree->right;

    return tree;
}

int height_AVLT(AvlTree tree) {
    if (tree) return tree->height;

    return -1;
}

static AvlTree singleRotateWithLeft(AvlTree k2) {
    Position_AVLT k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max_AVLT(height_AVLT(k2->left), height_AVLT(k2->right)) + 1;
    k1->height = max_AVLT(height_AVLT(k1->left), k2->height) + 1;

    return k1;
}

static AvlTree doubleRotateWithLeft(AvlTree k3) {
    k3->left = singleRotateWithRight(k3->left);

    return singleRotateWithLeft(k3);
}

static AvlTree singleRotateWithRight(AvlTree k1) {
    Position_AVLT k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max_AVLT(height_AVLT(k1->left), height_AVLT(k1->right)) + 1;
    k2->height = max_AVLT(height_AVLT(k1->right), k1->height) + 1;
    return k2;
}

static AvlTree doubleRotateWithRight(AvlTree k1) {
    k1->right = singleRotateWithLeft(k1->right);

    return singleRotateWithRight(k1);
}

AvlTree delete_AVLT(AvlTree tree, DataType_AVLT data) {
    Comparable result = COMPARE_WITH(tree->data, data);

    if (result == GT) {
        tree->left = delete_AVLT(tree->left, data);
        tree = betaIsOrNotRotateWithRight(tree, data);
        tree->height = max_AVLT(height_AVLT(tree->left), height_AVLT(tree->right)) + 1;
    } else if (result == LT) {
        tree->right = delete_AVLT(tree->right, data);
        tree = betaIsOrNotRotateWithLeft(tree, data);
        tree->height = max_AVLT(height_AVLT(tree->left), height_AVLT(tree->right)) + 1;
    } else if (tree->left && tree->right) {
        Position_AVLT tempCell = findMin_AVLT(tree->right);
        tree->data = tempCell->data;
        tree->right = delete_AVLT(tree->right, tree->data);
    } else {
        Position_AVLT tempCell = tree;
        if (!tree->left)
            tree = tree->right;
        else if (!tree->right)
            tree = tree->left;

        free(tempCell);
    }

    return tree;
}

static AvlTree betaIsOrNotRotateWithRight(AvlTree tree, DataType_AVLT data) {
    if (abs(height_AVLT(tree->right) - height_AVLT(tree->left)) == 2) {
        if (COMPARE_WITH(tree->right->data, data) == LT)
            tree = singleRotateWithRight(tree);
        else
            tree = doubleRotateWithRight(tree);
    }
    return tree;
}

static AvlTree betaIsOrNotRotateWithLeft(AvlTree tree, DataType_AVLT data) {
    if (abs(height_AVLT(tree->left) - height_AVLT(tree->right)) == 2) {
        if (COMPARE_WITH(tree->left->data, data) == GT)
            tree = singleRotateWithLeft(tree);
        else
            tree = doubleRotateWithLeft(tree);
    }
    return tree;
}

static int max_AVLT(int num, int another) {
    return num > another ? num : another;
}

AvlTree insert_AVLT(AvlTree tree, DataType_AVLT data) {
    if (tree == NULL) {
        tree = malloc(sizeof(struct Node_AVLT));
        assert(tree);

        tree->data = data;
        tree->left = tree->right = NULL;
        tree->height = 0;
    } else if (COMPARE_WITH(tree->data, data) == GT) {
        tree->left = insert_AVLT(tree->left, data);
        tree = betaIsOrNotRotateWithLeft(tree, data);
    } else if (COMPARE_WITH(tree->data, data) == LT) {
        tree->right = insert_AVLT(tree->right, data);
        tree = betaIsOrNotRotateWithRight(tree, data);
    }


    int leftHeight = height_AVLT(tree->left);
    int rightHeight = height_AVLT(tree->right);

    tree->height = max_AVLT(leftHeight, rightHeight) + 1;
    return tree;
}

DataType_AVLT retrieve_AVLT(Position_AVLT pos) {
    return pos->data;
}

void preTraversal_AVLT(AvlTree tree) {
    if (!tree) return;

    PRINT_FMT(tree->data);
    preTraversal_AVLT(tree->left);
    preTraversal_AVLT(tree->right);
}

void middleTraversal_AVLT(AvlTree tree) {
    if (!tree) return;

    middleTraversal_AVLT(tree->left);
    PRINT_FMT(tree->data);
    middleTraversal_AVLT(tree->right);
}

void behindTraversal_AVLT(AvlTree tree) {
    if (!tree) return;

    behindTraversal_AVLT(tree->left);
    behindTraversal_AVLT(tree->right);
    PRINT_FMT(tree->data);
}

void levelTraversal_AVLT(AvlTree tree) {
    if (!tree) return;
    LinkedQueue queue = newLinkedQueue();
    enqueue_LQ(queue, tree);

    while (!isEmpty_LQ(queue)) {
        Position_AVLT node = frontAndDequeue_LQ(queue);
        PRINT_FMT(node->data);
        if (node->left)
            enqueue_LQ(queue, node->left);
        if (node->right)
            enqueue_LQ(queue, node->right);
    }

    puts("\n");
}

int size_AVLT(AvlTree tree) {
    int size = 0;

    if (tree) {
        size++;
        size += size_AVLT(tree->left);
        size += size_AVLT(tree->right);
    }

    return size;
}

bool isEmpty_AVLT(AvlTree tree) {
    return tree == NULL;
}