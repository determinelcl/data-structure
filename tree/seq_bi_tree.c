//
// Created by determination on 2018/9/16.
//
#include "seq_bi_tree.h"

#define EMPTY 0

static int depthFor_SBT(SeqBinaryTree tree, int index);

static bool isEmptyOfData_SBT(SeqBinaryTree tree, int index);

SeqBinaryTree newSeqBinaryTree(int maxSize) {
    SeqBinaryTree tree = malloc(sizeof(SeqBiTreeNode));
    tree->data = malloc(sizeof(DataType_SBT) * maxSize);

    for (int i = 0; i < maxSize; i++)
        tree->data[i] = EMPTY_OF_DATA_SBT;

    tree->length = EMPTY;
    tree->capacity = maxSize;
    return tree;
}

bool isFull_SBT(SeqBinaryTree tree) {
    return tree->capacity == tree->length;
}

bool add_SBT(SeqBinaryTree tree, DataType_SBT data) {
    if (isFull_SBT(tree)) return false;

    for (int i = 0; i < tree->capacity; ++i) {
        if (tree->data[i] != EMPTY_OF_DATA_SBT) continue;

        tree->data[i] = data;
        tree->length++;
        break;
    }
    return true;
}

bool isEmpty_SBT(SeqBinaryTree tree) {
    assert(tree);

    return tree->length == EMPTY;
}

static int depthFor_SBT(SeqBinaryTree tree, int index) {
    if (!isEmptyOfData_SBT(tree, index - 1)) {
        int depthOfLeft = depthFor_SBT(tree, 2 * index + 1) + 1;
        int depthOfRight = depthFor_SBT(tree, 2 * index + 2) + 1;
        return depthOfLeft > depthOfRight ? depthOfLeft : depthOfRight;
    }
    return 0;
}

int depth_SBT(SeqBinaryTree tree) {
    assert(tree);
    return depthFor_SBT(tree, 0);
}

DataType_SBT root_SBT(SeqBinaryTree tree) {
    if (isEmpty_SBT(tree))
        return EMPTY_OF_DATA_SBT;

    return tree->data[0];
}


DataType_SBT parent_SBT(SeqBinaryTree tree, DataType_SBT data) {
    assert(tree);
    if (isEmpty_SBT(tree)) return NOT_FOUND_SBT;

    for (int i = 1; i <= tree->length - 1; i++)
        if (tree->data[i] == data)
            return tree->data[(i - 1) / 2];

    return NOT_FOUND_SBT;
}


DataType_SBT leftChild_SBT(SeqBinaryTree tree, DataType_SBT data) {
    if (isEmpty_SBT(tree)) return NOT_FOUND_SBT;

    for (int i = 0; i <= tree->length - 1; i++)
        if (tree->data[i] == data) {
            int index = i * 2 + 1;
            if (index >= tree->capacity)
                return NOT_FOUND_SBT;
            return tree->data[index];
        }

    return NOT_FOUND_SBT;
}

DataType_SBT rightChild_SBT(SeqBinaryTree tree, DataType_SBT data) {
    if (isEmpty_SBT(tree)) return NOT_FOUND_SBT;

    for (int i = 0; i <= tree->length - 1; i++)
        if (tree->data[i] == data) {
            int index = i * 2 + 2;
            if (index >= tree->capacity)
                return NOT_FOUND_SBT;
            return tree->data[index];
        }

    return NOT_FOUND_SBT;
}

DataType_SBT leftSibling_SBT(SeqBinaryTree tree, DataType_SBT data) {
    if (isEmpty_SBT(tree)) return NOT_FOUND_SBT;

    for (int i = 1; i <= tree->length - 1; i++)
        if (tree->data[i] == data && i % 2 == 0)
            return tree->data[i - 1];

    return NOT_FOUND_SBT;
}

DataType_SBT rightSibling_SBT(SeqBinaryTree tree, DataType_SBT data) {
    if (isEmpty_SBT(tree)) return NOT_FOUND_SBT;

    for (int i = 1; i <= tree->length - 1; i++)
        if (tree->data[i] == data && i % 2)
            return tree->data[i + 1];

    return NOT_FOUND_SBT;
}


static void preTraversalIn_SBT(SeqBinaryTree tree, int index) {
    printf("%d\t", tree->data[index]);
    if (!isEmptyOfData_SBT(tree, 2 * index + 1))
        preTraversalIn_SBT(tree, 2 * index + 1);
    if (!isEmptyOfData_SBT(tree, 2 * index + 2))
        preTraversalIn_SBT(tree, 2 * index + 2);
}

void preTraversal_SBT(SeqBinaryTree tree) {
    if (!isEmpty_SBT(tree))
        preTraversalIn_SBT(tree, 0);
    puts("\n");
}

static void middleTraversalIn_SBT(SeqBinaryTree tree, int index) {
    if (!isEmptyOfData_SBT(tree, 2 * index + 1))
        middleTraversalIn_SBT(tree, 2 * index + 1);

    printf("%d\t", tree->data[index]);

    if (!isEmptyOfData_SBT(tree, 2 * index + 2))
        middleTraversalIn_SBT(tree, 2 * index + 2);
}

void middleTraversal_SBT(SeqBinaryTree tree) {
    if (!isEmpty_SBT(tree))
        middleTraversalIn_SBT(tree, 0);
    puts("\n");
}

static void behindTraversalIn_SBT(SeqBinaryTree tree, int index) {
    if (!isEmptyOfData_SBT(tree, 2 * index + 1))
        behindTraversalIn_SBT(tree, 2 * index + 1);
    if (!isEmptyOfData_SBT(tree, 2 * index + 2))
        behindTraversalIn_SBT(tree, 2 * index + 2);

    printf("%d\t", tree->data[index]);
}

static bool isEmptyOfData_SBT(SeqBinaryTree tree, int index) {
    if (index >= tree->capacity) return true;

    return tree->data[index] == EMPTY_OF_DATA_SBT;
}

void behindTraversal_SBT(SeqBinaryTree tree) {
    if (!isEmpty_SBT(tree))
        behindTraversalIn_SBT(tree, 0);

    puts("\n");
}

void levelTraversal_SBT(SeqBinaryTree tree) {
    for (int i = 0; i < tree->capacity; i++)
        if (tree->data[i] != EMPTY_OF_DATA_SBT)
            printf("%d\t", tree->data[i]);

    puts("\n");
}

int size_SBT(SeqBinaryTree tree) {
    return tree->length;
}

int capacity_SBT(SeqBinaryTree tree) {
    return tree->capacity;
}

bool isExist_SBT(SeqBinaryTree tree, DataType_SBT data) {
    for (int i = 0; i < tree->capacity; ++i)
        if (tree->data[i] == data) return true;

    return false;
}