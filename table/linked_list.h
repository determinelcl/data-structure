//
//  linked_list.h
//  data-structure
//
//  Created by determination on 2018/8/26.
//  Copyright © 2018年 determination. All rights reserved.
//

#ifndef linked_list_h
#define linked_list_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int DataType_LL;
typedef struct Node {
    DataType_LL data;
    struct Node * next;
} *NODE;

typedef NODE LinkedList;
typedef NODE Position_LL;

// 新建一个链表
bool newLinkedList(LinkedList *list);

// 判断链表是否为空
bool isEmpty_LL(LinkedList list);

// 是否是最后一个节点
bool isLast_LL(Position_LL pos, LinkedList list);

// 查找链表中包含此数据的节点
Position_LL find_LL(DataType_LL data, LinkedList list);

// 从链表中删除指定的数据
void delete_LL(DataType_LL data, LinkedList list);

// 查找当前数据的前一个数据
Position_LL findPrevious_LL(DataType_LL data, LinkedList list);

// 向链表中添加数据
void add_LL(DataType_LL data, LinkedList list, Position_LL pos);

// 清空链表
void clear_LL(LinkedList list);

// 获取头指针
Position_LL header_LL(LinkedList list);

// 返回链表的第一个元素
Position_LL first_LL(LinkedList list);

// 返回当前元素的下一个元素
Position_LL advance_LL(Position_LL pos);

// 返回此位置的数据域
DataType_LL retrieve_LL(Position_LL pos);

// ADT接口声明
/**
    根据索引查找元素，将查找的元素存放在Position之中
    返回值：成功查找则返回OK，否则返回ERROR
 */
bool get_LL(LinkedList list, int index, Position_LL pos);

// 返回链表中元素的个数
int size_LL(LinkedList list);

// 显示链表中的数据
void showList_LL(LinkedList list);

#endif /* linked_list_h */
