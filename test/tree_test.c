//
// Created by determination on 2018/9/8.
//

#include "tree_test.h"

void testBinary_Tree(void) {
    printf("*****************************************************\n");
    printf("*                    二叉树测试                      *\n");
    printf("*****************************************************\n");
    BinaryTree tree = newBinaryTree();
    printf("二叉树是否为空:%s\n", isEmpty_BT(tree) ? "是" : "否");

    printf("向二叉树中的左子树插入元素\n");
    const int SIZE = 10;
    int leftChild[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int rightChild[SIZE] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

    for (int i = 0; i < SIZE; ++i) {
        insert_BT(tree, &leftChild[i], LEFT_CHILD);
    }

    printf("二叉树是否为空:%s\n", isEmpty_BT(tree) ? "是" : "否");
    printf("节点数目%d\n", size_BT(tree));
    printf("先序遍历：\n");
    preTraversal_BT(tree);
    printf("中序遍历：\n");
    middleTraversal_BT(tree);
    printf("后序遍历：\n");
    behindTraversal_BT(tree);
    printf("层序遍历：\n");
    levelTraversal_BT(tree);

    printf("向二叉树中的右子树插入元素\n");
    for (int i = 0; i < SIZE; ++i) {
        insert_BT(tree, &rightChild[i], RIGHT_CHILD);
    }

    printf("二叉树是否为空:%s\n", isEmpty_BT(tree) ? "是" : "否");
    printf("节点数目%d\n", size_BT(tree));
    printf("先序遍历：\n");
    preTraversal_BT(tree);
    printf("中序遍历：\n");
    middleTraversal_BT(tree);
    printf("后序遍历：\n");
    behindTraversal_BT(tree);
    printf("层序遍历：\n");
    levelTraversal_BT(tree);
}