//
// Created by determination on 2018/10/8.
//

#ifndef HELLO_HUFFMAN_TREE_H
#define HELLO_HUFFMAN_TREE_H

#include "tree_generic.h"
#include <string.h>


#define N_HT 4
#define M_HT (2 * N_HT - 1)   // n个叶子节点构造的哈夫曼树有2n-1个结点

typedef char DataType;

typedef struct {
    unsigned int weight;// 权值只能是正数
    int parent;
    int left;
    int right;
} HuffmanRecord;

typedef HuffmanRecord HuffmanTree[M_HT + 1];  // 第一个单元不用

typedef char *HuffmanCode[N_HT + 1];   // 存储每个字符的哈夫曼编码表

/**
 * 构造哈夫曼树
 *
 * @param tree 哈夫曼树
 * @param weight 所给定的权值
 * @param countOfCh 给定需要构造表的长度
 */
void createHuffmanTree(HuffmanTree tree, const unsigned *weight, int countOfCh);

/**
 * 在HT[1...k]里选择parent为0的且权值最小的2结点，
 * 其序号分别为firstMinIndex,secondMinIndex，parent不为0说明该结点已经参与构造了，故不许再考虑
 *
 * @param tree 哈夫曼树
 * @param maxPreIndex 已经构造了的节点的最大的索引
 * @param firstMinIndex 将找到的第一个节点的索引存储的地址
 * @param secondMinIndex 将找到的第二个节点的索引存储的地址
 */
void select_HT(HuffmanTree tree, int maxPreIndex, int *firstMinIndex, int *secondMinIndex);

/**
 * 打印哈夫曼树
 *
 * @param tree 哈夫曼树
 * @param data 对应的字符
 */
void printHuffmanTree_HT(HuffmanTree tree, char *data);

/**
 * 为每个字符求解哈夫曼编码，从叶子到根逆向求解每个字符的哈夫曼编码
 *
 * @param tree 构造完成哈夫曼树
 * @param huffmanCode 将哈夫曼树中的数据对其进行编码后的结果集
 */
void encodingHuffmanCode_HT(HuffmanTree tree, HuffmanCode huffmanCode);

/**
 * 打印哈夫曼编码表
 *
 * @param tree 哈夫曼树
 * @param ch 根据编码的字符进行打印与之对应的编码
 */
void printHuffmanCoding_HT(HuffmanCode tree, char *ch);

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
void decodingHuffmanCode_HT(HuffmanTree tree, const char *ch, const char *decodingStr, int lenOfDecStr, char *result);

#endif //HELLO_HUFFMAN_TREE_H
