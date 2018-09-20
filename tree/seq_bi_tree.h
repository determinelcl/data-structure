//
// Created by determination on 2018/9/16.
//

#ifndef HELLO_SEQ_BINARY_SEARCH_H
#define HELLO_SEQ_BINARY_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef int DataType_SBT;

typedef struct{
    DataType_SBT * data;
    int length;
    int capacity;
} SeqBiTreeNode, *SeqBinaryTree;

//typedef struct {
//    int level, order; // 结点的层,本层序号(按满二叉树计算)
//} Position_SBT;




#endif //HELLO_SEQ_BINARY_SEARCH_H
