//
// Created by determination on 2018/9/8.
//

#include "binary_tree.h"
#include "linked_queue.h"

#define EMPTY -1


void init_BT(BinaryTree tree) {
    assert(tree != NULL);

    tree->root = NULL;
    tree->size = EMPTY;
}

bool isEmpty_BT(BinaryTree tree) {
    return tree->size == EMPTY;
}

static bool insertNode_BT(PtrToNode_BT *tree, DataType_BT data) {
    if (*tree == NULL) {
        *tree = (PtrToNode_BT) malloc(sizeof(struct TreeNode_BT));
        assert(tree != NULL);

        (*tree)->data = data;
        return true;
    } else if ((*tree)->left != NULL && (*tree)->right == NULL) {
        return insertNode_BT(&(*tree)->right, data);
    } else {
        return insertNode_BT(&(*tree)->left, data);
    }
}

bool insert_BT(BinaryTree tree, DataType_BT data, int flag) {
    assert(tree != NULL);

    if (tree->root == NULL) {
        tree->root = (PtrToNode_BT) malloc(sizeof(struct TreeNode_BT));
        assert(tree->root != NULL);

        tree->root->data = data;
        tree->size++;
        return true;
    }

    // 用于判断是要插入左子树还是右子树
    flag == LEFT_BT ?
    insertNode_BT(&tree->root->left, data)
                    :
    insertNode_BT(&tree->root->right, data);

    tree->size++;
    return true;
}

static void pTraversal_BT(PtrToNode_BT tree) {
    if (tree == NULL) return;
    printf("%d\t", tree->data);
    pTraversal_BT(tree->left);
    pTraversal_BT(tree->right);
}

void preTraversal_BT(BinaryTree tree) {
    if (tree == NULL || tree->size == EMPTY) return;
    pTraversal_BT(tree->root);
    printf("\n\n");
}

static void mTraversal_BT(PtrToNode_BT tree) {
    if (tree == NULL) return;
    pTraversal_BT(tree->left);
    printf("%d\t", tree->data);
    pTraversal_BT(tree->right);
}

void middleTraversal_BT(BinaryTree tree) {
    if (tree == NULL || tree->size == EMPTY) return;
    mTraversal_BT(tree->root);
    printf("\n\n");
}

static void beTraversal_BT(PtrToNode_BT tree) {
    if (tree == NULL) return;
    pTraversal_BT(tree->left);
    pTraversal_BT(tree->right);
    printf("%d\t", tree->data);
}

void behandTraversal_BT(BinaryTree tree) {
    if (tree == NULL || tree->size == EMPTY) return;
    beTraversal_BT(tree->root);
    printf("\n\n");
}

void levelTraversal_BT(BinaryTree tree) {
    if (tree == NULL || tree->size == EMPTY) return;

    LinkedQueue queue = (LinkedQueue) malloc(sizeof(Queue_LQ));
    initLinkedQueue(queue);

    enqueue_LQ(queue, tree->root);
    while (!isEmpty_LQ(queue)) {
        PtrToNode_BT node = frontAndDequeue_LQ(queue);
        printf("%d\t", node->data);

        if (node->left != NULL)
            enqueue_LQ(queue, node->left);

        if (node->right != NULL)
            enqueue_LQ(queue, node->right);
    }

    printf("\n\n");
}



