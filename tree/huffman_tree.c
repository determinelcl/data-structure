//
// Created by determination on 2018/10/8.
//

#include "huffman_tree.h"

/**
 * 构造哈夫曼树
 *
 * @param tree 哈夫曼树
 * @param weight 所给定的权值
 * @param countOfCh 给定需要构造表的长度
 */
void createHuffmanTree(HuffmanTree tree, const unsigned *weight, int countOfCh) {
    if (countOfCh <= 1)
        return;

    for (int i = 1; i <= countOfCh; i++) {
        tree[i].weight = weight[i];
        tree[i].left = 0;
        tree[i].parent = 0;
        tree[i].right = 0;
    }

    for (int i = countOfCh + 1; i <= M_HT; i++) {
        tree[i].weight = 0;
        tree[i].left = 0;
        tree[i].parent = 0;
        tree[i].right = 0;
    }

    int firstMinIndex, secondMinIndex;
    for (int i = countOfCh + 1; i <= M_HT; i++) {
        select_HT(tree, i - 1, &firstMinIndex, &secondMinIndex);
        tree[firstMinIndex].parent = i;
        tree[secondMinIndex].parent = i;
        tree[i].left = firstMinIndex;
        tree[i].right = secondMinIndex;
        tree[i].weight = tree[firstMinIndex].weight + tree[secondMinIndex].weight;
    }
}

/**
 * 在tree[最小的index...k]里选择parent为0的且权值最小的两个结点，
 * 其序号分别为firstMinIndex,secondMinIndex，parent不为0说明该结点已经参与构造了，故不许再考虑
 *
 * @param tree 哈夫曼树
 * @param maxPreIndex 已经构造了的节点的最大的索引
 * @param firstMinIndex 将找到的第一个节点的索引存储的地址
 * @param secondMinIndex 将找到的第二个节点的索引存储的地址
 */
void select_HT(HuffmanTree tree, int maxPreIndex, int *firstMinIndex, int *secondMinIndex) {
    unsigned minWeight = 65536, minWeightIndex = 1;

    // 搜索权值最小的节点坐标
    for (unsigned i = minWeightIndex; i <= maxPreIndex; i++) {
        if (tree[i].parent) continue;

        if (minWeight < tree[i].weight) continue;

        minWeight = tree[i].weight;
        minWeightIndex = i;
    }

    *firstMinIndex = minWeightIndex;

    minWeight = 65536, minWeightIndex = 1;
    for (unsigned i = minWeightIndex; i <= maxPreIndex; i++) {
        if (tree[i].parent || i == *firstMinIndex) continue;

        if (minWeight < tree[i].weight) continue;
        minWeight = tree[i].weight;
        minWeightIndex = i;
    }

    *secondMinIndex = minWeightIndex;
}


/**
 * 打印哈夫曼树
 *
 * @param tree 哈夫曼树
 * @param data 对应的字符
 */
void printHuffmanTree_HT(HuffmanTree tree, char *data) {
    printf("\n");
    printf("data, weight, parent, left, right\n");
    for (int i = 1; i <= M_HT; i++) {
        if (i > N_HT) {
            printf("  -, %5d, %5d, %5d, %5d\n", tree[i].weight, tree[i].parent, tree[i].left, tree[i].right);
        } else {
            printf("  %c, %5d, %5d, %5d, %5d\n", data[i], tree[i].weight, tree[i].parent, tree[i].left, tree[i].right);
        }
    }
    printf("\n");
}

/**
 * 为每个字符求解哈夫曼编码，从叶子到根逆向求解每个字符的哈夫曼编码
 *
 * @param tree 构造完成哈夫曼树
 * @param huffmanCode 将哈夫曼树中的数据对其进行编码后的结果集
 */
void encodingHuffmanCode_HT(HuffmanTree tree, HuffmanCode huffmanCode) {
    char tmpCode[N_HT];
    tmpCode[N_HT - 1] = '\0';                  // 编码的结束符

    int startIndex, currentIndex, parentIndexForCurr;
    for (int i = 1; i <= N_HT; i++) {
        startIndex = N_HT - 1;
        currentIndex = i;
        parentIndexForCurr = tree[i].parent;

        // 用于构造编码
        while (parentIndexForCurr) {
            if (tree[parentIndexForCurr].left == currentIndex)
                tmpCode[--startIndex] = '0';
            else // 相当于比较的是右节点
                tmpCode[--startIndex] = '1';

            currentIndex = parentIndexForCurr;
            parentIndexForCurr = tree[currentIndex].parent;
        }

        // 存放有几个编码，就分配多少内存空间，并将编码信息复制到哈夫曼编码集中
        huffmanCode[i] = (char *) malloc((N_HT - startIndex) * sizeof(char));
        strncpy(huffmanCode[i], &tmpCode[startIndex], N_HT - startIndex);
    }
}

/**
 * 打印哈夫曼编码表
 *
 * @param tree 哈夫曼树
 * @param ch 根据编码的字符进行打印与之对应的编码
 */
void printHuffmanCoding_HT(HuffmanCode tree, char *ch) {
    printf("\n");
    for (int i = 1; i <= N_HT; i++) {
        printf("%c:%s\n", ch[i], tree[i]);
    }
    printf("\n");
}

/**
 * 解码过程：从哈夫曼树的根节点出发，按字符'0'或'1'
 * 确定找其左孩子或右孩子，直至找到叶子节点即可，便求得该字串相应的字符
 *
 * @param tree 构造之后的哈夫曼树
 * @param ch 哈夫曼编码所对应的编码之前的字符
 * @param decodingStr 要解码的哈夫曼编码
 * @param lenOfDecStr 要解码的哈夫曼编码的长度
 * @param result 解析完成之后的字符串
 */
void decodingHuffmanCode_HT(HuffmanTree tree, const char *ch, const char *decodingStr, int lenOfDecStr, char *result) {
    int root = M_HT;
    int decodingStrCursor = 0;

    int resultStrCursor = 0;
    while (decodingStrCursor < lenOfDecStr) {
        if (decodingStr[decodingStrCursor] == '0')
            root = tree[root].left;
        else if (decodingStr[decodingStrCursor] == '1')
            root = tree[root].right;

        if (root <= N_HT) {
            result[resultStrCursor] = ch[root];
            resultStrCursor++;
            root = M_HT;
        }
        decodingStrCursor++;
    }

    result[resultStrCursor] = '\0';
}