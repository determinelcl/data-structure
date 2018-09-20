//
// Created by determination on 2018/9/16.
//
#include "seq_bi_tree.h"
#include "avl_tree.h"

#define EMPTY_OF_DATA -32768
#define EMPTY 0

static int depthFor(SeqBinaryTree tree, int index);

SeqBinaryTree newSeqBinaryTree(int maxSize) {
    SeqBinaryTree tree = malloc(sizeof(SeqBiTreeNode));
    tree->data = malloc(sizeof(DataType_SBT) * maxSize);

    for (int i = 0; i < maxSize; i++)
        tree->data[i] = EMPTY_OF_DATA;

    tree->length = EMPTY;
    tree->capacity = maxSize;
    return tree;
}

bool isEmpty_SBT(SeqBinaryTree tree) {
    assert(tree);

    return tree->length == EMPTY;
}

static int depthFor(SeqBinaryTree tree, int index) {
    if (tree->length > index) {
        int depthOfLeft = depthFor(tree, 2 * index);
        int depthOfRight = depthFor(tree, 2 * index + 1);
        return depthOfLeft > depthOfRight ? depthOfLeft + 1 : depthOfRight + 1;
    }
    return 0;
}

int depth_SBT(SeqBinaryTree tree) {
    assert(tree);
    return depthFor(tree, 0);
}

DataType_SBT root_SBT(SeqBinaryTree tree) {
    if (isEmpty_SBT(tree))
        return EMPTY_OF_DATA;

    return tree->data[0];
}

//
//DataType_SBT Value(SeqBinaryTree T, Position_SBT e) { // 初始条件：二叉树T存在，e是T中某个结点(的位置)
//    // 操作结果：返回处于位置e(层,本层序号)的结点的值
//    return T[(int) pow(2, e.level - 1 + e.order - 2)];
//}
//
//bool Assign(SeqBinaryTree T, Position_SBT e, DataType_SBT value) { // 初始条件：二叉树T存在，e是T中某个结点(的位置)
//    // 操作结果：给处于位置e(层,本层序号)的结点赋新值value
//    int i = (int) pow(2, e.level - 1) + e.order - 2; // 将层、本层序号转为矩阵的序号
//    if (value && !T[(i + 1) / 2 - 1]) // 给叶子赋非空值但双亲为空
//        return false;
//    else if (!value && (T[i * 2 + 1] || T[i * 2 + 2])) // 给双亲赋空值但有叶子(不空)
//        return false;
//    T[i] = value;
//    return true;
//}
//
//DataType_SBT Parent(SeqBinaryTree T, DataType_SBT e) { // 初始条件：二叉树T存在，e是T中某个结点
//    // 操作结果：若e是T的非根结点，则返回它的双亲；否则返回“空”
//    int i;
//    if (T[0]) // 空树
//        return -1;
//    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
//        if (T[i] == e) // 找到e
//            return T[(i + 1) / 2 - 1];
//    return -1; // 没找到e
//}
//
//DataType_SBT LeftChild(SeqBinaryTree T, DataType_SBT e) { // 初始条件：二叉树T存在，e是T中某个结点。操作结果：返回e的左孩子。若e无左孩子,则返回“空”
//    int i;
//    if (T[0]) // 空树
//        return -1;
//    for (i = 0; i <= MAX_TREE_SIZE - 1; i++)
//        if (T[i] == e) // 找到e
//            return T[i * 2 + 1];
//    return -1; // 没找到e
//}
//
//DataType_SBT RightChild(SeqBinaryTree T, DataType_SBT e) { // 初始条件：二叉树T存在，e是T中某个结点。操作结果：返回e的右孩子。若e无右孩子,则返回“空”
//    int i;
//    if (T[0]) // 空树
//        return -1;
//    for (i = 0; i <= MAX_TREE_SIZE - 1; i++)
//        if (T[i] == e) // 找到e
//            return T[i * 2 + 2];
//    return -1; // 没找到e
//}
//
//DataType_SBT LeftSibling(SeqBinaryTree T, DataType_SBT e) { // 初始条件：二叉树T存在，e是T中某个结点
//    // 操作结果：返回e的左兄弟。若e是T的左孩子或无左兄弟，则返回“空”
//    int i;
//    if (T[0]) // 空树
//        return -1;
//    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
//        if (T[i] == e && i % 2 == 0) // 找到e且其序号为偶数(是右孩子)
//            return T[i - 1];
//    return -1; // 没找到e
//}
//
//DataType_SBT RightSibling(SeqBinaryTree T, DataType_SBT e) { // 初始条件：二叉树T存在，e是T中某个结点
//    // 操作结果：返回e的右兄弟。若e是T的右孩子或无右兄弟，则返回“空”
//    int i;
//    if (T[0]) // 空树
//        return -1;
//    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
//        if (T[i] == e && i % 2) // 找到e且其序号为奇数(是左孩子)
//            return T[i + 1];
//    return -1; // 没找到e
//}
//
//void Move(SeqBinaryTree q, int j, SeqBinaryTree T, int i) // InsertChild()用到。加
//{ // 把从q的j结点开始的子树移为从T的i结点开始的子树
//    if (q[2 * j + 1]) // q的左子树不空
//        Move(q, (2 * j + 1), T, (2 * i + 1)); // 把q的j结点的左子树移为T的i结点的左子树
//    if (q[2 * j + 2]) // q的右子树不空
//        Move(q, (2 * j + 2), T, (2 * i + 2)); // 把q的j结点的右子树移为T的i结点的右子树
//    T[i] = q[j]; // 把q的j结点移为T的i结点
//    q[j] = 0; // 把q的j结点置空
//}
//
//void InsertChild(SeqBinaryTree T, DataType_SBT p, int LR,
//                 SeqBinaryTree c) { //初始条件：二叉树T存在，p是T中某个结点的值，LR为0或1，非空二叉树c与T不相交且右子树为空
//    //操作结果:根据LR为0或1,插入c为T中p结点的左或右子树。p结点的原有左或右子树则成为c的右子树
//    int j, k, i = 0;
//    for (j = 0; j < (int) pow(2, BiTreeDepth(T)) - 1; j++) // 查找p的序号
//        if (T[j] == p) // j为p的序号
//            break;
//    k = 2 * j + 1 + LR; // k为p的左或右孩子的序号
//    if (T[k] != NULL) // p原来的左或右孩子不空
//        Move(T, k, T, 2 * k + 2); // 把从T的k结点开始的子树移为从k结点的右子树开始的子树
//    Move(c, i, T, k); // 把从c的i结点开始的子树移为从T的k结点开始的子树
//}
//
//typedef int QElemType; // 设队列元素类型为整型(序号)
//#include "linked_queue.h"
//
//bool DeleteChild(SeqBinaryTree T, Position_SBT p, int LR) { // 初始条件：二叉树T存在，p指向T中某个结点，LR为1或0
//    // 操作结果：根据LR为1或0，删除T中p所指结点的左或右子树
//    int i;
//    bool k = true; // 队列不空的标志
//    LinkedQueue q = newLinkedQueue();
//
//    i = (int) pow(2, p.level - 1) + p.order - 2; // 将层、本层序号转为矩阵的序号
//    if (T[i]) // 此结点空
//        return false;
//    i = i * 2 + 1 + LR; // 待删除子树的根结点在矩阵中的序号
//    while (k) {
//        if (T[2 * i + 1]) // 左结点不空
//        {
//            int data = 2 * i + 1;
//            enqueue_LQ(q, &data);
//        } // 入队左结点的序号
//        if (T[2 * i + 2]) // 右结点不空
//        {
//            int num1 = 2 * i + 2;
//            enqueue_LQ(q, &num1);
//        } // 入队右结点的序号
//        T[i] = 0; // 删除此结点
//        k = enqueue_LQ(q, &i); // 队列不空
//    }
//    return true;
//}
//
//void (*VisitFunc)(DataType_SBT); // 函数变量
//void PreTraverse(SeqBinaryTree T, int e) { // PreOrderTraverse()调用
//    VisitFunc(T[e]);
//    if (T[2 * e + 1]) // 左子树不空
//        PreTraverse(T, 2 * e + 1);
//    if (T[2 * e + 2]) // 右子树不空
//        PreTraverse(T, 2 * e + 2);
//}
//
//void PreOrderTraverse(SeqBinaryTree T, void(*Visit)(DataType_SBT)) { // 初始条件：二叉树存在，Visit是对结点操作的应用函数
//    // 操作结果：先序遍历T，对每个结点调用函数Visit一次且仅一次
//    VisitFunc = Visit;
//    if (!isEmpty_SBT(T)) // 树不空
//        PreTraverse(T, 0);
//    puts("\n");
//}
//
//void InTraverse(SeqBinaryTree T, int e) { // InOrderTraverse()调用
//    if (T[2 * e + 1]) // 左子树不空
//        InTraverse(T, 2 * e + 1);
//    VisitFunc(T[e]);
//    if (T[2 * e + 2]) // 右子树不空
//        InTraverse(T, 2 * e + 2);
//}
//
//void InOrderTraverse(SeqBinaryTree T, void(*Visit)(DataType_SBT)) { // 初始条件：二叉树存在，Visit是对结点操作的应用函数
//    // 操作结果：中序遍历T，对每个结点调用函数Visit一次且仅一次
//    VisitFunc = Visit;
//    if (!isEmpty_SBT(T)) // 树不空
//        InTraverse(T, 0);
//    puts("\n");
//}
//
//void PostTraverse(SeqBinaryTree T, int e) { // PostOrderTraverse()调用
//    if (T[2 * e + 1]) // 左子树不空
//        PostTraverse(T, 2 * e + 1);
//    if (T[2 * e + 2]) // 右子树不空
//        PostTraverse(T, 2 * e + 2);
//    VisitFunc(T[e]);
//}
//
//void PostOrderTraverse(SeqBinaryTree T, void(*Visit)(DataType_SBT)) { // 初始条件：二叉树T存在，Visit是对结点操作的应用函数
//    // 操作结果：后序遍历T，对每个结点调用函数Visit一次且仅一次
//    VisitFunc = Visit;
//    if (!isEmpty_SBT(T)) // 树不空
//        PostTraverse(T, 0);
//    puts("\n");
//}
//
//void LevelOrderTraverse(SeqBinaryTree T, void(*Visit)(DataType_SBT)) { // 层序遍历二叉树
//    int i = MAX_TREE_SIZE - 1, j;
//    while (T[i])
//        i--; // 找到最后一个非空结点的序号
//    for (j = 0; j <= i; j++) // 从根结点起，按层序遍历二叉树
//        if (T[j])
//            Visit(T[j]); // 只遍历非空的结点
//    puts("\n");
//}
//
//void Print(SeqBinaryTree T) { // 逐层、按本层序号输出二叉树
//    int j, k;
//    Position_SBT p;
//    DataType_SBT e;
//    for (j = 1; j <= BiTreeDepth(T); j++) {
//        printf("第%d层", j);
//        for (k = 1; k <= pow(2, j - 1); k++) {
//            p.level = j;
//            p.order = k;
//            e = Value(T, p);
//            if (e)
//                printf("%d：%d", k, e);
//        }
//        puts("\n");
//    }
//}