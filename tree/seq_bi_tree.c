//
// Created by determination on 2018/9/16.
//
#include "seq_bi_tree.h"

#define EMPTY_OF_DATA -32768
#define EMPTY 0

static int depthFor_SBT(SeqBinaryTree tree, int index);

SeqBinaryTree newSeqBinaryTree(int maxSize) {
    SeqBinaryTree tree = malloc(sizeof(SeqBiTreeNode));
    tree->data = malloc(sizeof(DataType_SBT) * maxSize);

    for (int i = 0; i < maxSize; i++)
        tree->data[i] = EMPTY_OF_DATA;

    tree->length = EMPTY;
    tree->capacity = maxSize;
    return tree;
}

bool isEmpty_SBT(SeqBinaryTree tree) {
    assert(tree);

    return tree->length == EMPTY;
}

static int depthFor_SBT(SeqBinaryTree tree, int index) {
    if (tree->length > index) {
        int depthOfLeft = depthFor_SBT(tree, 2 * index);
        int depthOfRight = depthFor_SBT(tree, 2 * index + 1);
        return depthOfLeft > depthOfRight ? depthOfLeft + 1 : depthOfRight + 1;
    }
    return 0;
}

int depth_SBT(SeqBinaryTree tree) {
    assert(tree);
    return depthFor_SBT(tree, 0);
}

DataType_SBT root_SBT(SeqBinaryTree tree) {
    if (isEmpty_SBT(tree))
        return EMPTY_OF_DATA;

    return tree->data[0];
}


DataType_SBT parent_SBT(SeqBinaryTree tree, DataType_SBT data) {
    assert(tree);
    if (isEmpty_SBT(tree)) return EMPTY_OF_DATA;

    for (int i = 1; i <= tree->length - 1; i++) {
        if (tree->data[i] == data)
            return tree->data[(i - 1) / 2];
    }

    return EMPTY_OF_DATA;
}


DataType_SBT leftChild_SBT(SeqBinaryTree tree, DataType_SBT data) {
    if (isEmpty_SBT(tree)) return EMPTY_OF_DATA;

    for (int i = 0; i <= tree->length - 1; i++)
        if (tree->data[i] == data)
            return tree->data[i * 2 + 1];

    return EMPTY_OF_DATA;
}

DataType_SBT rightChild_SBT(SeqBinaryTree tree, DataType_SBT data) {
    if (isEmpty_SBT(tree)) return EMPTY_OF_DATA;

    for (int i = 0; i <= tree->length - 1; i++)
        if (tree->data[i] == data)
            return tree->data[i * 2 + 2];
    return data;
}

DataType_SBT leftSibling_SBT(SeqBinaryTree tree, DataType_SBT data) {
    if (isEmpty_SBT(tree)) return EMPTY_OF_DATA;

    for (int i = 1; i <= tree->length - 1; i++)
        if (tree->data[i] == data && i % 2 == 0)
            return tree->data[i - 1];

    return EMPTY_OF_DATA;
}

DataType_SBT rightSibling_SBT(SeqBinaryTree tree, DataType_SBT data) {
    if (isEmpty_SBT(tree)) return EMPTY_OF_DATA;

    for (int i = 1; i <= tree->length - 1; i++)
        if (tree->data[i] == data && i % 2)
            return tree->data[i + 1];

    return EMPTY_OF_DATA;
}


static void preTraversalIn_SBT(SeqBinaryTree tree, int index) {
    printf("%d\t", tree->data[index]);
    if (tree->data[2 * index + 1] != EMPTY_OF_DATA)
        preTraversalIn_SBT(tree, 2 * index + 1);
    if (tree->data[2 * index + 2] != EMPTY_OF_DATA)
        preTraversalIn_SBT(tree, 2 * index + 2);
}

void preTraversal_SBT(SeqBinaryTree tree) {
    if (!isEmpty_SBT(tree))
        preTraversalIn_SBT(tree, 0);
    puts("\n");
}

static void middleTraversalIn_SBT(SeqBinaryTree tree, int index) {
    if (tree->data[2 * index + 1] != EMPTY_OF_DATA)
        middleTraversalIn_SBT(tree, 2 * index + 1);

    printf("%d\t", tree->data[index]);

    if (tree->data[2 * index + 2] != EMPTY_OF_DATA)
        middleTraversalIn_SBT(tree, 2 * index + 2);
}

void middleTraversal_SBT(SeqBinaryTree tree) {
    if (!isEmpty_SBT(tree))
        middleTraversalIn_SBT(tree, 0);
    puts("\n");
}

static void behindTraversalIn_SBT(SeqBinaryTree tree, int index) {
    if (tree->data[2 * index + 1] != EMPTY_OF_DATA)
        behindTraversalIn_SBT(tree, 2 * index + 1);
    if (tree->data[2 * index + 2] != EMPTY_OF_DATA)
        behindTraversalIn_SBT(tree, 2 * index + 2);

    printf("%d\t", tree->data[index]);
}

void behindTraversal_SBT(SeqBinaryTree tree) {
    if (!isEmpty_SBT(tree))
        behindTraversalIn_SBT(tree, 0);
    puts("\n");
}

void LevelOrderTraverse(SeqBinaryTree tree) {
    for (int i = 0; i <= tree->capacity; i++)
        if (tree->data[i] != EMPTY_OF_DATA)
            printf("%d\t", tree->data[i]);

    puts("\n");
}