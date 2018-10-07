//
// Created by determination on 2018/9/8.
//

#include "binary_tree.h"

#define EMPTY_OF_DATA_SBT 0


BinaryTree newBinaryTree() {
    BinaryTree tree = (BinaryTree) malloc(sizeof(struct BiTree));
    assert(tree != NULL);

    tree->root = NULL;
    tree->size = EMPTY_OF_DATA_SBT;

    return tree;
}

static void initTreeNode(PtrToNode_BT node) {
    node->right = NULL;
    node->left = NULL;
}

bool isEmpty_BT(BinaryTree tree) {
    return tree->size == EMPTY_OF_DATA_SBT;
}

static PtrToNode_BT createNode_BT() {
    PtrToNode_BT tree = (PtrToNode_BT) malloc(sizeof(struct TreeNode_BT));
    assert(tree != NULL);
    initTreeNode(tree);
    return tree;
}

static bool insertNodeL_BT(PtrToNode_BT *tree, DataType_BT data) {
    if (*tree == NULL) {
        *tree = createNode_BT();
        (*tree)->data = data;
        return true;
    } else if ((*tree)->left != NULL && (*tree)->right == NULL) {
        return insertNodeL_BT(&(*tree)->right, data);
    } else {
        return insertNodeL_BT(&(*tree)->left, data);
    }
}

static bool insertNodeR_BT(PtrToNode_BT *tree, DataType_BT data) {
    if (*tree == NULL) {
        *tree = createNode_BT();
        (*tree)->data = data;
        return true;
    } else if ((*tree)->right != NULL && (*tree)->left == NULL) {
        return insertNodeR_BT(&(*tree)->left, data);
    } else {
        return insertNodeR_BT(&(*tree)->right, data);
    }
}

bool insert_BT(BinaryTree tree, DataType_BT data, ChildTree flag) {
    assert(tree != NULL);

    if (tree->root == NULL) {
        tree->root = (PtrToNode_BT) malloc(sizeof(struct TreeNode_BT));
        assert(tree->root != NULL);

        tree->root->data = data;
        initTreeNode(tree->root);
        tree->size++;
        return true;
    }

    // 用于判断是要插入左子树还是右子树
    flag == LEFT_CHILD ?
    insertNodeL_BT(&tree->root->left, data)
                       :
    insertNodeR_BT(&tree->root->right, data);

    tree->size++;
    return true;
}

static void printData(PtrToNode_BT tree) {
    printf("%d\t", *(int *) tree->data);
}

static void pTraversal_BT(PtrToNode_BT tree) {
    if (tree == NULL) return;
    printData(tree);
    pTraversal_BT(tree->left);
    pTraversal_BT(tree->right);
}

void preTraversal_BT(BinaryTree tree) {
    if (tree == NULL || tree->size == EMPTY_OF_DATA_SBT) return;
    pTraversal_BT(tree->root);
    printf("\n\n");
}

static void mTraversal_BT(PtrToNode_BT tree) {
    if (tree == NULL) return;
    mTraversal_BT(tree->left);
    printData(tree);
    mTraversal_BT(tree->right);
}

void middleTraversal_BT(BinaryTree tree) {
    if (tree == NULL || tree->size == EMPTY_OF_DATA_SBT) return;
    mTraversal_BT(tree->root);
    printf("\n\n");
}

static void beTraversal_BT(PtrToNode_BT tree) {
    if (tree == NULL) return;
    beTraversal_BT(tree->left);
    beTraversal_BT(tree->right);
    printData(tree);
}

void behindTraversal_BT(BinaryTree tree) {
    if (tree == NULL || tree->size == EMPTY_OF_DATA_SBT) return;
    beTraversal_BT(tree->root);
    printf("\n\n");
}

void levelTraversal_BT(BinaryTree tree) {
    if (tree == NULL || tree->size == EMPTY_OF_DATA_SBT) return;

    LinkedQueue queue = newLinkedQueue();

    enqueue_LQ(queue, tree->root);
    while (!isEmpty_LQ(queue)) {
        PtrToNode_BT node = frontAndDequeue_LQ(queue);
        printData(node);

        if (node->left != NULL)
            enqueue_LQ(queue, node->left);

        if (node->right != NULL)
            enqueue_LQ(queue, node->right);
    }

    printf("\n\n");
}

int size_BT(BinaryTree tree) {
    return tree->size;
}



