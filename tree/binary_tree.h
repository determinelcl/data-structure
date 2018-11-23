//
// Created by determination on 2018/9/8.
//

#ifndef HELLO_TREE_LR_H
#define HELLO_TREE_LR_H

#include "tree_generic.h"
#include "linked_queue.h"

#define CREATE_NULL_FLAG -100

typedef int DataType_BT;
typedef struct TreeNode_BT *PtrToNode_BT;


struct TreeNode_BT {
    DataType_BT data;
    PtrToNode_BT left;
    PtrToNode_BT right;
};

typedef struct BiTree {
    PtrToNode_BT root;
    int size;
} *BinaryTree;

typedef enum {
    LEFT_CHILD, RIGHT_CHILD
} ChildTree;

/**
 * 根据扩展的先序序列构建二叉树
 *
 * @param nodeData 需要构建节点的节点数据
 * @param numOfData 节点数据的数量
 * @return 构造完成的二叉树
 */
BinaryTree createBinaryTree(DataType_BT *nodeData);

/**
 * 使用先序序列和中序序列构建二叉树
 *
 * @param prevArray 先序序列
 * @param middleArray 中序序列
 * @param size 序列中的字符的个数
 * @return 构建完成的二叉树
 */
BinaryTree createBinaryTree2(DataType_BT *prevArray, DataType_BT *middleArray, int size);

BinaryTree newBinaryTree(void);

bool isEmpty_BT(BinaryTree tree);

bool insert_BT(BinaryTree tree, DataType_BT data, ChildTree flag);

void preTraversal_BT(BinaryTree tree);

void middleTraversal_BT(BinaryTree tree);

void behindTraversal_BT(BinaryTree tree);

void levelTraversal_BT(BinaryTree tree);

int size_BT(BinaryTree tree);


#endif //HELLO_TREE_LR_H
