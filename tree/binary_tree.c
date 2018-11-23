//
// Created by determination on 2018/9/8.
//

#include "binary_tree.h"

#define EMPTY_OF_DATA_BT 0

static PtrToNode_BT createBiTree_BT(DataType_BT *data, int *index, int *numOfData);

PtrToNode_BT createBiTree2_BT(const DataType_BT *prevArray, const DataType_BT *middleArray, int *sizeOfData, int n);

BinaryTree createBinaryTree(DataType_BT *nodeData) {
    BinaryTree binaryTree = newBinaryTree();

    int rootIndex = 0;

    binaryTree->root = createBiTree_BT(nodeData, &rootIndex, &binaryTree->size);

    return binaryTree;
}

static PtrToNode_BT createBiTree_BT(DataType_BT *data, int *index, int *numOfData) {
    DataType_BT nodeData = data[(*index)++];
    if (nodeData == CREATE_NULL_FLAG)
        return NULL;

    PtrToNode_BT root = malloc(sizeof(struct TreeNode_BT));
    assert(root);
    root->data = nodeData;
    root->left = createBiTree_BT(data, index, numOfData);
    root->right = createBiTree_BT(data, index, numOfData);
    (*numOfData)++;
    return root;
}

BinaryTree createBinaryTree2(DataType_BT *prevArray, DataType_BT *middleArray, int size) {
    BinaryTree binaryTree = newBinaryTree();
    binaryTree->root = createBiTree2_BT(prevArray, middleArray, &binaryTree->size, size);
    binaryTree->size = size;
    return binaryTree;
}

PtrToNode_BT createBiTree2_BT(const DataType_BT *prevArray, const DataType_BT *middleArray, int *sizeOfData, int n) {
    if (n == 0) return NULL;

    PtrToNode_BT root = malloc(sizeof(struct TreeNode_BT));
    assert(root);

    DataType_BT ch = prevArray[0];
    root->data = ch;

    int lfArray[n], rfArray[n];
    int lcArray[n], rcArray[n];
    int ln, rn, i, j;

    for (i = 0; middleArray[i] != ch; i++)      // 左子树的中序
        lcArray[i] = middleArray[i];

    ln = i;
    i++;
    for (rn = 0; i < n; rn++, i++)              // 右子树的中序
        rcArray[rn] = middleArray[i];


    for (i = 0; i < ln; i++)                    // 左子树的先序
        lfArray[i] = prevArray[i + 1];


    for (j = 0; j < rn; j++, i++)               // 右子树的先序
        rfArray[j] = prevArray[i + 1];


    root->left = createBiTree2_BT(lfArray, lcArray, sizeOfData, ln);//以当前节点的左指针为下一级二叉树的跟
    root->right = createBiTree2_BT(rfArray, rcArray, sizeOfData, rn);//以当前节点的右指针为下一级二叉树的跟
    return root;
}

BinaryTree newBinaryTree() {
    BinaryTree tree = (BinaryTree) malloc(sizeof(struct BiTree));
    assert(tree != NULL);

    tree->root = NULL;
    tree->size = EMPTY_OF_DATA_BT;

    return tree;
}

static void initTreeNode(PtrToNode_BT node) {
    node->right = NULL;
    node->left = NULL;
}

bool isEmpty_BT(BinaryTree tree) {
    return tree->size == EMPTY_OF_DATA_BT;
}

static PtrToNode_BT createNode_BT() {
    PtrToNode_BT tree = (PtrToNode_BT) malloc(sizeof(struct TreeNode_BT));
    assert(tree != NULL);
    initTreeNode(tree);
    return tree;
}

static bool insertNodeL_BT(PtrToNode_BT *tree, DataType_BT data) {
    if (*tree == NULL) {
        *tree = createNode_BT();
        (*tree)->data = data;
        return true;
    } else if ((*tree)->left != NULL && (*tree)->right == NULL) {
        return insertNodeL_BT(&(*tree)->right, data);
    } else {
        return insertNodeL_BT(&(*tree)->left, data);
    }
}

static bool insertNodeR_BT(PtrToNode_BT *tree, DataType_BT data) {
    if (*tree == NULL) {
        *tree = createNode_BT();
        (*tree)->data = data;
        return true;
    } else if ((*tree)->right != NULL && (*tree)->left == NULL) {
        return insertNodeR_BT(&(*tree)->left, data);
    } else {
        return insertNodeR_BT(&(*tree)->right, data);
    }
}

bool insert_BT(BinaryTree tree, DataType_BT data, ChildTree flag) {
    assert(tree != NULL);

    if (tree->root == NULL) {
        tree->root = (PtrToNode_BT) malloc(sizeof(struct TreeNode_BT));
        assert(tree->root != NULL);

        tree->root->data = data;
        initTreeNode(tree->root);
        tree->size++;
        return true;
    }

    // 用于判断是要插入左子树还是右子树
    flag == LEFT_CHILD ?
    insertNodeL_BT(&tree->root->left, data)
                       :
    insertNodeR_BT(&tree->root->right, data);

    tree->size++;
    return true;
}

static void printData(PtrToNode_BT tree) {
    printf("%d\t", tree->data);
}

static void pTraversal_BT(PtrToNode_BT tree) {
    if (tree == NULL) return;
    printData(tree);
    pTraversal_BT(tree->left);
    pTraversal_BT(tree->right);
}

void preTraversal_BT(BinaryTree tree) {
    if (tree == NULL || tree->size == EMPTY_OF_DATA_BT) return;
    pTraversal_BT(tree->root);
    printf("\n\n");
}

static void mTraversal_BT(PtrToNode_BT tree) {
    if (tree == NULL) return;
    mTraversal_BT(tree->left);
    printData(tree);
    mTraversal_BT(tree->right);
}

void middleTraversal_BT(BinaryTree tree) {
    if (tree == NULL || tree->size == EMPTY_OF_DATA_BT) return;
    mTraversal_BT(tree->root);
    printf("\n\n");
}

static void beTraversal_BT(PtrToNode_BT tree) {
    if (tree == NULL) return;
    beTraversal_BT(tree->left);
    beTraversal_BT(tree->right);
    printData(tree);
}

void behindTraversal_BT(BinaryTree tree) {
    if (tree == NULL || tree->size == EMPTY_OF_DATA_BT) return;
    beTraversal_BT(tree->root);
    printf("\n\n");
}

void levelTraversal_BT(BinaryTree tree) {
    if (tree == NULL || tree->size == EMPTY_OF_DATA_BT) return;

    LinkedQueue queue = newLinkedQueue();

    enqueue_LQ(queue, tree->root);
    while (!isEmpty_LQ(queue)) {
        PtrToNode_BT node = frontAndDequeue_LQ(queue);
        printData(node);

        if (node->left != NULL)
            enqueue_LQ(queue, node->left);

        if (node->right != NULL)
            enqueue_LQ(queue, node->right);
    }

    printf("\n\n");
}

int size_BT(BinaryTree tree) {
    return tree->size;
}



