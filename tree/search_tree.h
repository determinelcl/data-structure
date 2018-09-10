//
// Created by determination on 2018/9/8.
//

#ifndef HELLO_SEARCH_TREE_H
#define HELLO_SEARCH_TREE_H

#include "tree_generic.h"

typedef struct TreeNode_ST *Position_ST;
typedef struct TreeNode_ST *SearchTree;

typedef void *DataType_ST;

struct TreeNode_ST {
    DataType_ST data;
    SearchTree left;
    SearchTree right;
};

SearchTree newSearchTree(void);

SearchTree makeEmpty_ST(SearchTree tree);

Position_ST find_ST(SearchTree tree, DataType_ST data);

Position_ST findMin_ST(SearchTree tree);

Position_ST findMax_ST(SearchTree tree);

SearchTree insert_ST(SearchTree tree, DataType_ST data);

SearchTree delete_ST(SearchTree tree, DataType_ST data);

DataType_ST retrieve_ST(Position_ST pos);

void preTraversal_ST(SearchTree tree);

void middleTraversal_ST(SearchTree tree);

void behindTraversal_ST(SearchTree tree);

void levelTraversal_ST(SearchTree tree);

int size_ST(SearchTree tree);

bool isEmpty_ST(SearchTree tree);


#endif //HELLO_SEARCH_TREE_H
