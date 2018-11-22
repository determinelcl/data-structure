#include <stdio.h>
#include "table_test.h"
#include "tree_test.h"
#include "graph_test.h"


int main() {
    testArrayList();
    testLinkedList();
    testLinkedList2();
    testLinkedListO();
    testLinkedList2O();
    testArrayStack();
    testLinkedStack();
    testArrayQueueO();
    testLinkedQueue();

    testBinary_Tree();
    testSearchTree();
    testAvlTree();
    testSeqBinaryTree();
    testHuffmanTree();
    testLHuffmanTree();

    testAdjMatrixGraph();
    testAdjTableGraph();
    testCrossListGraph();
    testAdjMultipleTableGraph();
    return 0;
}