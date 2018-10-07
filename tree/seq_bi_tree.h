//
// Created by determination on 2018/9/16.
//

#ifndef HELLO_SEQ_BINARY_SEARCH_H
#define HELLO_SEQ_BINARY_SEARCH_H

#include "tree_generic.h"
#define EMPTY_OF_DATA_SBT -32768
#define NOT_FOUND_SBT -1

typedef int DataType_SBT;

typedef struct {
    DataType_SBT *data;
    int length;
    int capacity;
} SeqBiTreeNode, *SeqBinaryTree;

SeqBinaryTree newSeqBinaryTree(int maxSize);

bool add_SBT(SeqBinaryTree tree, DataType_SBT data);

bool isFull_SBT(SeqBinaryTree tree);

bool isEmpty_SBT(SeqBinaryTree tree);

bool isExist_SBT(SeqBinaryTree tree, DataType_SBT data);

int depth_SBT(SeqBinaryTree tree);

DataType_SBT root_SBT(SeqBinaryTree tree);

DataType_SBT parent_SBT(SeqBinaryTree tree, DataType_SBT data);

DataType_SBT leftChild_SBT(SeqBinaryTree tree, DataType_SBT data);

DataType_SBT rightChild_SBT(SeqBinaryTree tree, DataType_SBT data);

DataType_SBT leftSibling_SBT(SeqBinaryTree tree, DataType_SBT data);

DataType_SBT rightSibling_SBT(SeqBinaryTree tree, DataType_SBT data);

void preTraversal_SBT(SeqBinaryTree tree);

void middleTraversal_SBT(SeqBinaryTree tree);

void behindTraversal_SBT(SeqBinaryTree tree);

void levelTraversal_SBT(SeqBinaryTree tree);

int size_SBT(SeqBinaryTree tree);

int capacity_SBT(SeqBinaryTree tree);

#endif //HELLO_SEQ_BINARY_SEARCH_H
