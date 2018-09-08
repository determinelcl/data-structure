//
// Created by determination on 2018/9/8.
//

#ifndef HELLO_TREE_LR_H
#define HELLO_TREE_LR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define LEFT_BT 0
#define RIGHT_BT 1

typedef int DataType_BT;
typedef struct TreeNode_BT *PtrToNode_BT;


struct TreeNode_BT {
    DataType_BT data;
    PtrToNode_BT left;
    PtrToNode_BT right;
};

typedef struct {
    PtrToNode_BT root;
    int size;
}* BinaryTree;

void init_BT(BinaryTree tree);

bool insert_BT(BinaryTree tree, DataType_BT data, int flag);

void preTraversal_BT(BinaryTree tree);

void middleTraversal_BT(BinaryTree tree);

void behandTraversal_BT(BinaryTree tree);

void levelTraversal_BT(BinaryTree tree);


#endif //HELLO_TREE_LR_H
