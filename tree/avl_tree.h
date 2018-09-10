//
// Created by determination on 2018/9/10.
//

#ifndef HELLO_AVL_TREE_H
#define HELLO_AVL_TREE_H

#include "tree_generic.h"
#include "linked_queue.h"
#include <math.h>

typedef struct Node_AVLT *Position_AVLT;
typedef struct Node_AVLT *AvlTree;
typedef void *DataType_AVLT;

struct Node_AVLT {
    DataType_AVLT data;
    int height;
    AvlTree left;
    AvlTree right;
};

AvlTree newAvlTree(void);

AvlTree makeEmpty_AVLT(AvlTree tree);

Position_AVLT find_AVLT(AvlTree tree, DataType_AVLT data);

Position_AVLT findMin_AVLT(AvlTree tree);

Position_AVLT findMax_AVLT(AvlTree tree);

AvlTree insert_AVLT(AvlTree tree, DataType_AVLT data);

AvlTree delete_AVLT(AvlTree tree, DataType_AVLT data);

DataType_AVLT retrieve_AVLT(Position_AVLT pos);

int height_AVLT(AvlTree tree);

void preTraversal_AVLT(AvlTree tree);

void middleTraversal_AVLT(AvlTree tree);

void behindTraversal_AVLT(AvlTree tree);

void levelTraversal_AVLT(AvlTree tree);

int size_AVLT(AvlTree tree);

bool isEmpty_AVLT(AvlTree tree);


#endif //HELLO_AVL_TREE_H
