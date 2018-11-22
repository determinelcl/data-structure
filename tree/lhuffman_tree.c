//
// Created by determination on 2018/11/21.
//

#include "lhuffman_tree.h"
#include <string.h>

void findTwoMinWeight(LHuffmanTree *treeNodes, LHuffmanTree *firstMin, LHuffmanTree *secondMin, int capacity);

LHuffmanTree newEmpty_LHT(int weight);

void deleteChildNodeFrom(LHuffmanTree *treeNodes, LHuffmanTree firstMin, LHuffmanTree secondMin, int *capacity);

void putParentNodeInto(LHuffmanTree *treeNodes, LHuffmanTree parent, int sizeOfWeights, int *capacity);

void encode_LHT(LHuffmanTree tree, char **encodeArr, char *code, char *str);

int indexOf_LHT(DataType_LHT ch, char *str);

LHuffmanTree createLHuffmanTree(int *weight, DataType_LHT *str, int sizeOfWeights) {

    // 将所有权值存放入n个树节点
    LHuffmanTree treeNodes[sizeOfWeights];
    for (int i = 0; i < sizeOfWeights; i++) {
        treeNodes[i] = newEmpty_LHT(weight[i]);
        treeNodes[i]->data = str[i];
    }


    LHuffmanTree firstMin = newEmpty_LHT(0), secondMin = newEmpty_LHT(0);

    int capacity = sizeOfWeights;
    while (capacity != 1) {
        // 查找两个权值最小的
        findTwoMinWeight(treeNodes, &firstMin, &secondMin, capacity);

        // 构建一颗简单的二叉树
        LHuffmanTree parent = newEmpty_LHT(firstMin->weight + secondMin->weight);
        parent->left = firstMin;
        parent->right = secondMin;
        firstMin->parent = parent;
        secondMin->parent = parent;

        // 从集合总删除两个子节点，并把父节点放入集合
        deleteChildNodeFrom(treeNodes, firstMin, secondMin, &capacity);
        putParentNodeInto(treeNodes, parent, sizeOfWeights, &capacity);
    }


    return treeNodes[0];
}

void putParentNodeInto(LHuffmanTree *treeNodes, LHuffmanTree parent, int sizeOfWeights, int *capacity) {
    assert(*capacity < sizeOfWeights);

    treeNodes[*capacity] = parent;
    (*capacity)++;
}

void deleteChildNodeFrom(LHuffmanTree *treeNodes, LHuffmanTree firstMin, LHuffmanTree secondMin, int *capacity) {

    int delFirst = -1, delSecond = -1;
    for (int i = 0; i < *capacity; i++) {
        if (treeNodes[i] == firstMin)
            delFirst = i;
        else if (treeNodes[i] == secondMin)
            delSecond = i;
    }

    for (int i = delFirst; i < *capacity; i++) {
        treeNodes[i] = treeNodes[i + 1];
    }
    (*capacity)--;


    int startIndex = delFirst < delSecond ? delSecond - 1 : delSecond;
    for (int i = startIndex; i < *capacity; i++) {
        treeNodes[i] = treeNodes[i + 1];
    }
    (*capacity)--;
}

LHuffmanTree newEmpty_LHT(int weight) {
    LHuffmanTree leaf = malloc(sizeof(struct LHT));
    assert(leaf);
    leaf->weight = weight;
    leaf->right = NULL;
    leaf->left = NULL;
    leaf->parent = NULL;
    return leaf;
}

void findTwoMinWeight(LHuffmanTree *treeNodes, LHuffmanTree *firstMin, LHuffmanTree *secondMin, int capacity) {
    LHuffmanTree temp = treeNodes[0];

    for (int i = 1; i < capacity; ++i) {
        if (temp->weight < treeNodes[i]->weight) continue;
        temp = treeNodes[i];
    }

    *firstMin = temp;


    LHuffmanTree secondTemp = treeNodes[0];
    int startIndex = 1;
    if (secondTemp == temp) {
        secondTemp = treeNodes[1];
        startIndex = 2;
    }

    for (int i = startIndex; i < capacity; i++) {
        if (treeNodes[i] == temp || secondTemp->weight < treeNodes[i]->weight) continue;

        secondTemp = treeNodes[i];
    }

    *secondMin = secondTemp;
}

void showHuffmanTree_LHT(LHuffmanTree tree) {
    if (!tree) {
        printf("^\t");
        return;
    }

    printf("%d\t", tree->weight);
    showHuffmanTree_LHT(tree->left);
    showHuffmanTree_LHT(tree->right);
}

void encodeHuffmanTree_LHT(LHuffmanTree tree, char *str, char **encodeArr) {
    assert(tree);

    encode_LHT(tree->left, encodeArr, "0", str);
    encode_LHT(tree->right, encodeArr, "1", str);
}

void encode_LHT(LHuffmanTree tree, char **encodeArr, char *code, char *str) {
    if (!tree) {
        return;
    }

    if (!tree->left && !tree->right) {
        int index = indexOf_LHT(tree->data, str);
        assert(index != -1);

        char *tempStr = malloc(sizeof(DataType_LHT) * strlen(encodeArr[index]));
        strncat(tempStr, encodeArr[index], strlen(encodeArr[index]));
        strncat(tempStr, code, strlen(code));
        encodeArr[index] = tempStr;
        return;
    }


    char *tempCode = malloc(sizeof(DataType_LHT) * strlen(code));
    strcat(tempCode, code);
    encode_LHT(tree->left, encodeArr, strncat(tempCode, "0", 1), str);

    tempCode = malloc(sizeof(DataType_LHT) * strlen(code));
    strcat(tempCode, code);
    encode_LHT(tree->right, encodeArr, strncat(tempCode, "1", 1), str);
}

int indexOf_LHT(DataType_LHT ch, char *str) {
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == ch)
            return i;
    }
    return -1;
}


void printHuffmanCode_LHT(char *str, char **encodeArr) {
    for (int i = 0; i < strlen(str); ++i) {
        printf("%c:%s\n", str[i], encodeArr[i]);
    }
    printf("\n\n");
}


int calculateWPL_LHT(int *weight, char **encodeArr, int sizeOfWeight) {
    int wpl = 0;

    for (int i = 0; i < sizeOfWeight; ++i) {
        wpl+= weight[i] * strlen(encodeArr[i]);
    }

    return wpl;
}