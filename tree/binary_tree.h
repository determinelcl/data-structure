//
// Created by determination on 2018/9/8.
//

#ifndef HELLO_TREE_LR_H
#define HELLO_TREE_LR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "linked_queue.h"

typedef void* DataType_BT;
typedef struct TreeNode_BT *PtrToNode_BT;


struct TreeNode_BT {
    DataType_BT data;
    PtrToNode_BT left;
    PtrToNode_BT right;
};

typedef struct BiTree{
    PtrToNode_BT root;
    int size;
}* BinaryTree;

typedef enum {
    LEFT_CHILD, RIGHT_CHILD
} ChildTree;

BinaryTree newBinaryTree(void);

bool isEmpty_BT(BinaryTree tree);

bool insert_BT(BinaryTree tree, DataType_BT data, ChildTree flag);

void preTraversal_BT(BinaryTree tree);

void middleTraversal_BT(BinaryTree tree);

void behindTraversal_BT(BinaryTree tree);

void levelTraversal_BT(BinaryTree tree);

int size_BT(BinaryTree tree);


#endif //HELLO_TREE_LR_H
