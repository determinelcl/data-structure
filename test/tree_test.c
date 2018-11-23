//
// Created by determination on 2018/9/8.
//

#include "tree_test.h"

void testBinary_Tree(void) {
    printf("*****************************************************\n");
    printf("*               二叉树链式存储结构测试例程             *\n");
    printf("*****************************************************\n");
    BinaryTree tree = newBinaryTree();
    printf("二叉树是否为空:%s\n", isEmpty_BT(tree) ? "是" : "否");

    printf("向二叉树中的左子树插入元素\n");
    const int SIZE = 10;
    int leftChild[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int rightChild[SIZE] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

    for (int i = 0; i < SIZE; ++i) {
        insert_BT(tree, leftChild[i], LEFT_CHILD);
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
        insert_BT(tree, rightChild[i], RIGHT_CHILD);
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


    printf("使用扩展的先序序列进行构建二叉树：\n");
    int null = CREATE_NULL_FLAG;
    int data[] = {1, 2, 4, 6, null, null, null, 5, null, null, 3, 7, null, null, 8, null, null};
    BinaryTree newBinaryTree = createBinaryTree(data);

    printf("二叉树是否为空:%s\n", isEmpty_BT(newBinaryTree) ? "是" : "否");
    printf("节点数目%d\n", size_BT(newBinaryTree));
    printf("先序遍历：\n");
    preTraversal_BT(newBinaryTree);
    printf("中序遍历：\n");
    middleTraversal_BT(newBinaryTree);
    printf("后序遍历：\n");
    behindTraversal_BT(newBinaryTree);
    printf("层序遍历：\n");
    levelTraversal_BT(newBinaryTree);

    printf("使用先序序列和中序序列进行构建二叉树：\n");
    const int SIZE_SERI = 8;
    int preArr[SIZE_SERI] = {1, 2, 4, 6, 5, 3, 7, 8};
    int inArr[SIZE_SERI] = {6, 4, 2, 5, 1, 7, 3, 8};
    BinaryTree tree2 = createBinaryTree2(preArr, inArr, SIZE_SERI);

    printf("二叉树是否为空:%s\n", isEmpty_BT(tree2) ? "是" : "否");
    printf("节点数目%d\n", size_BT(tree2));
    printf("先序遍历：\n");
    preTraversal_BT(tree2);
    printf("中序遍历：\n");
    middleTraversal_BT(tree2);
    printf("后序遍历：\n");
    behindTraversal_BT(tree2);
    printf("层序遍历：\n");
    levelTraversal_BT(tree2);

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
    preTraversal_ST(tree);
    puts("\n");
    printf("中序遍历：\n");
    middleTraversal_ST(tree);
    puts("\n");
    printf("后序遍历：\n");
    behindTraversal_ST(tree);
    puts("\n");
    printf("层序遍历：\n");
    levelTraversal_ST(tree);
    puts("\n");

    int num = 102;
    printf("向二叉搜索树中插入一个元素：%d\n", num);
    insert_ST(tree, &num);
    printf("二叉搜索树是否为空: %s\n", isEmpty_ST(tree) ? "是" : "否");
    printf("二叉搜索树的元素数为：%d\n", size_ST(tree));
    printf("先序遍历：\n");
    preTraversal_ST(tree);
    puts("\n");
    printf("中序遍历：\n");
    middleTraversal_ST(tree);
    puts("\n");
    printf("后序遍历：\n");
    behindTraversal_ST(tree);
    puts("\n");
    printf("层序遍历：\n");
    levelTraversal_ST(tree);
    puts("\n");

    printf("二叉搜索树中最大的元素为：%d\n", *(int *) retrieve_ST(findMax_ST(tree)));
    printf("二叉搜索树中最小的元素为：%d\n", *(int *) retrieve_ST(findMin_ST(tree)));

    printf("查找元素为%d的节点\n", num);
    DataType_ST findData = retrieve_ST(find_ST(tree, &num));
    printf("查找到的元素为：%d\n", *(int *) findData);
    delete_ST(tree, findData);

    printf("二叉搜索树是否为空: %s\n", isEmpty_ST(tree) ? "是" : "否");
    printf("二叉搜索树的元素数为：%d\n", size_ST(tree));
    printf("先序遍历：\n");
    preTraversal_ST(tree);
    puts("\n");
    printf("中序遍历：\n");
    middleTraversal_ST(tree);
    puts("\n");
    printf("后序遍历：\n");
    behindTraversal_ST(tree);
    puts("\n");
    printf("层序遍历：\n");
    levelTraversal_ST(tree);
    puts("\n");

    printf("二叉搜索树中最大的元素为：%d\n", *(int *) retrieve_ST(findMax_ST(tree)));
    printf("二叉搜索树中最小的元素为：%d\n", *(int *) retrieve_ST(findMin_ST(tree)));

    printf("清空二叉搜索树\n");
    tree = makeEmpty_ST(tree);
    printf("二叉搜索树是否为空: %s\n", isEmpty_ST(tree) ? "是" : "否");
    printf("二叉搜索树的元素数为：%d\n", size_ST(tree));

    puts("\n");
}

void testAvlTree(void) {
    printf("*****************************************************\n");
    printf("*                   AVL平衡树测试例程                 *\n");
    printf("*****************************************************\n");

    AvlTree tree = newAvlTree();
    const int SIZE = 10;
    int data[SIZE] = {6, 7, 8, 2, 1, 9, 10, 3, 4, 5};

    printf("AVL平衡树是否为空: %s\n", isEmpty_AVLT(tree) ? "是" : "否");
    printf("AVL平衡树的元素数为：%d\n", size_AVLT(tree));
    printf("AVL平衡树的高度为：%d\n", height_AVLT(tree));
    printf("向AVL平衡树中插入%d个元素\n", SIZE);

    for (int i = 0; i < SIZE; ++i) {
        tree = insert_AVLT(tree, &data[i]);
    }

    printf("AVL平衡树是否为空: %s\n", isEmpty_AVLT(tree) ? "是" : "否");
    printf("AVL平衡树的元素数为：%d\n", size_AVLT(tree));
    printf("AVL平衡树左子树的高度为：%d，右子树的高度为：%d\n", height_AVLT(tree->left), height_AVLT(tree->right));
    printf("先序遍历：\n");
    preTraversal_AVLT(tree);
    puts("\n");
    printf("中序遍历：\n");
    middleTraversal_AVLT(tree);
    puts("\n");
    printf("后序遍历：\n");
    behindTraversal_AVLT(tree);
    puts("\n");
    printf("层序遍历：\n");
    levelTraversal_AVLT(tree);
    puts("\n");

    int num = 102;
    printf("向AVL平衡树中插入一个元素：%d\n", num);
    insert_AVLT(tree, &num);
    printf("AVL平衡树是否为空: %s\n", isEmpty_AVLT(tree) ? "是" : "否");
    printf("AVL平衡树的元素数为：%d\n", size_AVLT(tree));
    printf("AVL平衡树左子树的高度为：%d，右子树的高度为：%d\n", height_AVLT(tree->left), height_AVLT(tree->right));
    printf("先序遍历：\n");
    preTraversal_AVLT(tree);
    puts("\n");
    printf("中序遍历：\n");
    middleTraversal_AVLT(tree);
    puts("\n");
    printf("后序遍历：\n");
    behindTraversal_AVLT(tree);
    puts("\n");
    printf("层序遍历：\n");
    levelTraversal_AVLT(tree);
    puts("\n");

    printf("AVL平衡树中最大的元素为：%d\n", *(int *) retrieve_AVLT(findMax_AVLT(tree)));
    printf("AVL平衡树中最小的元素为：%d\n", *(int *) retrieve_AVLT(findMin_AVLT(tree)));

    printf("查找元素为%d的节点\n", num);
    DataType_AVLT findData = retrieve_AVLT(find_AVLT(tree, &num));
    printf("查找到的元素为：%d\n", *(int *) findData);
    printf("删除元素：%d\n", *(int *) findData);
    delete_AVLT(tree, findData);

    printf("AVL平衡树是否为空: %s\n", isEmpty_AVLT(tree) ? "是" : "否");
    printf("AVL平衡树的元素数为：%d\n", size_AVLT(tree));
    printf("AVL平衡树左子树的高度为：%d，右子树的高度为：%d\n", height_AVLT(tree->left), height_AVLT(tree->right));
    printf("先序遍历：\n");
    preTraversal_AVLT(tree);
    puts("\n");
    printf("中序遍历：\n");
    middleTraversal_AVLT(tree);
    puts("\n");
    printf("后序遍历：\n");
    behindTraversal_AVLT(tree);
    puts("\n");
    printf("层序遍历：\n");
    levelTraversal_AVLT(tree);
    puts("\n");

    printf("AVL平衡树中最大的元素为：%d\n", *(int *) retrieve_AVLT(findMax_AVLT(tree)));
    printf("AVL平衡树中最小的元素为：%d\n", *(int *) retrieve_AVLT(findMin_AVLT(tree)));

    printf("清空AVL平衡树\n");
    tree = makeEmpty_AVLT(tree);
    printf("AVL平衡树是否为空: %s\n", isEmpty_AVLT(tree) ? "是" : "否");
    printf("AVL平衡树的元素数为：%d\n", size_AVLT(tree));
    printf("AVL平衡树的高度为：%d\n", height_AVLT(tree));
    puts("\n");
}

void testSeqBinaryTree(void) {
    printf("*****************************************************\n");
    printf("*                 二叉树顺序存储测试例程               *\n");
    printf("*****************************************************\n");


    const int maxSize = 10;
    printf("创建顺序存储二叉树, 最大容量为%d，并向二叉树中填充数据元素！\n", maxSize);
    SeqBinaryTree binaryTree = newSeqBinaryTree(maxSize);
    for (int i = 0; i < maxSize; ++i) {
        add_SBT(binaryTree, i + 1);
    }

    printf("顺序存储二叉树的数据元素的个数为：%d\n", size_SBT(binaryTree));
    printf("顺序存储二叉树的容量为：%d\n", capacity_SBT(binaryTree));
    printf("顺序存储二叉树的根元素为：%d\n", root_SBT(binaryTree));
    printf("顺序存储二叉树的深度为：%d\n\n", depth_SBT(binaryTree));

    printf("先序遍历：\n");
    preTraversal_SBT(binaryTree);
    puts("\n");
    printf("中序遍历：\n");
    middleTraversal_SBT(binaryTree);
    puts("\n");
    printf("后序遍历：\n");
    behindTraversal_SBT(binaryTree);
    puts("\n");
    printf("层序遍历：\n");
    levelTraversal_SBT(binaryTree);
    puts("\n");

    const int num1 = 7;
    const int num2 = 6;
    printf("顺序存储二叉树中\n");
    DataType_SBT parentOfNum = parent_SBT(binaryTree, num1);
    printf("元素%d和%d的父节点分别为：%d和%d\n", num1, num2, parentOfNum, parent_SBT(binaryTree, num2));
    printf("元素%d的右子节点元素为：%d\n", parentOfNum, rightChild_SBT(binaryTree, parentOfNum));
    printf("元素%d的左子节点元素为：%d\n", parentOfNum, leftChild_SBT(binaryTree, parentOfNum));
    printf("元素%d的左兄弟节点元素为：%d\n", num1, leftSibling_SBT(binaryTree, num1));
    printf("元素%d的右兄弟节点元素为：%d\n", num2, rightSibling_SBT(binaryTree, num2));
    printf("元素%d的右兄弟节点元素是否存在：%s\n", num2, isExist_SBT(binaryTree, num2) ? "存在" : "不存在");


    puts("\n");
}

void testHuffmanTree() {
    printf("*****************************************************\n");
    printf("*                  哈夫曼树测试例程                   *\n");
    printf("*****************************************************\n");

    HuffmanTree tree;

    DataType data[N_HT + 1] = {[1]='a', 'b', 'c', 'd'};
    unsigned weight[N_HT + 1] = {[1]=30, 5, 10, 20};

    // 构建哈夫曼编码表
    createHuffmanTree(tree, weight, N_HT);
    printHuffmanTree_HT(tree, data);

    HuffmanCode huffmanCode;
    encodingHuffmanCode_HT(tree, huffmanCode);
    printHuffmanCoding_HT(huffmanCode, data);


    char *testDecodingStr = "01000101101110";
    int testDecodingStrLen = 14;
    printf("编码%s对应的字符串是：", testDecodingStr);
    char result[30];
    decodingHuffmanCode_HT(tree, data, testDecodingStr, testDecodingStrLen, result);
    printf("%s\n", result);

    puts("\n");
}

void testLHuffmanTree(void) {
    printf("*****************************************************\n");
    printf("*                哈夫曼树链式存储测试例程              *\n");
    printf("*****************************************************\n");

    const int SIZE = 4;
    DataType_LHT *data = "abcd";
    int weight[SIZE] = {30, 5, 10, 20};
    LHuffmanTree tree = createLHuffmanTree(weight, data, SIZE);
    showHuffmanTree_LHT(tree);

    char *encodeStr[SIZE] = {"", "", "", ""};

    encodeHuffmanTree_LHT(tree, data, encodeStr);
    printHuffmanCode_LHT(data, encodeStr);

    printf("Huffman树的带权路径长度为：%d\n", calculateWPL_LHT(weight, encodeStr, SIZE));
    puts("\n");
}