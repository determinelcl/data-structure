//
// Created by determination on 2018/11/21.
//

#ifndef HELLO_LHUFFMAN_TREE_H
#define HELLO_LHUFFMAN_TREE_H

#include "tree_generic.h"

typedef char DataType_LHT;

typedef struct LHT {
    DataType_LHT data;
    int weight;// 权值只能是正数
    struct LHT *parent;
    struct LHT *left;
    struct LHT *right;
} *LHuffmanTree;

/**
 * 根据字符对应的权重值表来构造哈夫曼编码树
 *
 * @param weight 给定的字符
 * @param sizeOfWeights 表的大小
 * @return 构建完成的Huffman树
 */
LHuffmanTree createLHuffmanTree(int *weight, DataType_LHT *str, int sizeOfWeights);

/**
 * 先序遍历输出Huffman树
 *
 * @param tree Huffman树
 */
void showHuffmanTree_LHT(LHuffmanTree tree);

/**
 * 显示输出对应字符的哈夫曼编码
 *
 * @param tree 链式存储的Huffman树
 */
void encodeHuffmanTree_LHT(LHuffmanTree tree, char *str, char **encodeArr);

/**
 * 打印字符对应的Huffman编码
 *
 * @param str 对应的字符串
 * @param encodeArr 对应字符串的编码
 */
void printHuffmanCode_LHT(char *str, char **encodeArr);

/**
 * 计算WPL（最小带权路径长度）
 *
 * @param weight 权重值
 * @param encodeArr Huffman编码
 * @param sizeOfWeight 权重值的个数
 * @return 得出的wpl
 */
int calculateWPL_LHT(int *weight, char **encodeArr, int sizeOfWeight);

#endif //HELLO_LHUFFMAN_TREE_H
