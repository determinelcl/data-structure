//
//  linked_list_o.h
//  data-structure
//
//  Created by determination on 2018/8/28.
//  Copyright © 2018年 determination. All rights reserved.
//

#ifndef linked_list_o_h
#define linked_list_o_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define LEN sizeof(struct SCriculist)

typedef int* DataType_LLO;
typedef struct SCriculist  //定义结构体
{
    DataType_LLO data;                  //数据域
    struct SCriculist *next; //指针域
} *Position_LLO, *Criculist;


Criculist newLinkedListO(void);//创建单向循环链表函数
Position_LLO findPrevious_LLO(DataType_LLO data, Criculist list);
Position_LLO add_LLO(Criculist list,  DataType_LLO data);
void insert_LLO(Criculist list, int index, DataType_LLO data);//向单向循环链表位置为i的地方插入元素e
void delete_LLO(Criculist list, int index, DataType_LLO data);//从单向循环链表中删除位置为i的结点，并用e返回其数据域的值
Position_LLO find_LLO(Criculist list, int index); //查找单向循环链表中的第i个结点
int indexOf_LLO(Criculist list, DataType_LLO data); //查找单向循环链表中的第一个数据域为e的结点，输出该节点在链表中的位置
int size_LLO(Criculist list); //计算单向循环链表的长度
void showList_LLO(Criculist list);  //以此输出单向循环链表中的数据

#endif /* linked_list_o_h */
