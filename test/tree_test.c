//
// Created by determination on 2018/9/8.
//

#include "tree_test.h"

void testBinary_Tree(void) {
    printf("*****************************************************\n");
    printf("*                    二叉树测试例                    *\n");
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

    puts("\n");
}

void testSearchTree(void) {
    printf("*****************************************************\n");
    printf("*                  二叉搜索树测试例程                 *\n");
    printf("*****************************************************\n");

    SearchTree tree = newSearchTree();
    const int SIZE = 10;
    int data[SIZE] = {6, 7, 8, 2, 1, 9, 10, 3, 4, 5};

    printf("二叉搜索树是否为空: %s\n", isEmpty_ST(tree) ? "是" : "否");
    printf("二叉搜索树的元素数为：%d\n", size_ST(tree));
    printf("向二叉搜索树中插入%d个元素\n", SIZE);

    for (int i = 0; i < SIZE; ++i) {
        tree = insert_ST(tree, &data[i]);
    }

    printf("二叉搜索树是否为空: %s\n", isEmpty_ST(tree) ? "是" : "否");
    printf("二叉搜索树的元素数为：%d\n", size_ST(tree));
    printf("先序遍历：\n");
    preTraversal_ST(tree);puts("\n");
    printf("中序遍历：\n");
    middleTraversal_ST(tree);puts("\n");
    printf("后序遍历：\n");
    behindTraversal_ST(tree);puts("\n");
    printf("层序遍历：\n");
    levelTraversal_ST(tree);puts("\n");

    int num = 102;
    printf("向二叉搜索树中插入一个元素：%d", num);
    insert_ST(tree, &num);
    printf("二叉搜索树是否为空: %s\n", isEmpty_ST(tree) ? "是" : "否");
    printf("二叉搜索树的元素数为：%d\n", size_ST(tree));
    printf("先序遍历：\n");
    preTraversal_ST(tree);puts("\n");
    printf("中序遍历：\n");
    middleTraversal_ST(tree);puts("\n");
    printf("后序遍历：\n");
    behindTraversal_ST(tree);puts("\n");
    printf("层序遍历：\n");
    levelTraversal_ST(tree);puts("\n");

    printf("二叉搜索树中最大的元素为：%d\n", *(int *)retrieve_ST(findMax_ST(tree)));
    printf("二叉搜索树中最小的元素为：%d\n", *(int *)retrieve_ST(findMin_ST(tree)));
    
    printf("查找元素为%d的节点\n", num);
    DataType_ST findData = retrieve_ST(find_ST(tree, &num));
    printf("查找到的元素为：%d\n", *(int *) findData);
    delete_ST(tree, findData);

    printf("二叉搜索树是否为空: %s\n", isEmpty_ST(tree) ? "是" : "否");
    printf("二叉搜索树的元素数为：%d\n", size_ST(tree));
    printf("先序遍历：\n");
    preTraversal_ST(tree);puts("\n");
    printf("中序遍历：\n");
    middleTraversal_ST(tree);puts("\n");
    printf("后序遍历：\n");
    behindTraversal_ST(tree);puts("\n");
    printf("层序遍历：\n");
    levelTraversal_ST(tree);puts("\n");

    printf("二叉搜索树中最大的元素为：%d\n", *(int *)retrieve_ST(findMax_ST(tree)));
    printf("二叉搜索树中最小的元素为：%d\n", *(int *)retrieve_ST(findMin_ST(tree)));

    printf("清空二叉搜索书\n");
    tree = makeEmpty_ST(tree);
    printf("二叉搜索树是否为空: %s\n", isEmpty_ST(tree) ? "是" : "否");
    printf("二叉搜索树的元素数为：%d\n", size_ST(tree));

    puts("\n");
}