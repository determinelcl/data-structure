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
#include <assert.h>

typedef void* DataType_LL;
typedef struct Node {
    DataType_LL data;
    struct Node *next;
} *NODE;

typedef NODE LinkedList;
typedef NODE Position_LL;

/**
 * 新建一个链表
 *
 * @return 新的链表
 */
LinkedList newLinkedList(void);

/**
 * 判断链表是否为空
 *
 * @param list 当前链表
 * @return 为空返回true，否则返回false
 */
bool isEmpty_LL(LinkedList list);

/**
 * 验证当前节点是否是最后一个节点
 *
 * @param pos 要验证的节点
 * @param list 验证节点逻辑上附属的链表
 * @return 验证结果
 */
bool isLast_LL(LinkedList list, Position_LL pos);

/**
 * 验证指定位置的节点是否为头节点
 *
 * @param list 指定的链表
 * @param pos 验证的节点元素
 * @return 是否为头节点
 */
bool isHead_LL(LinkedList list, Position_LL pos);

/**
 * 查询指定数据在链表中的位置
 *
 * @param data 要查询的数据
 * @param list 要查询数据的链表
 * @return 此数据在链表中的位置的节点
 */
Position_LL find_LL(LinkedList list, DataType_LL data);

/**
 * 从链表中删除指定的数据
 *
 * @param data 指定的要删除的数据
 * @param list 删除数据的链表
 */
void delete_LL(LinkedList list, DataType_LL data);

/**
 * 查询指定数据所属节点的前面一个节点的位置
 *
 * @param data 要查询数据的前面的位置
 * @param list 要查询的链表
 * @return 指定数据的前面一个节点
 */
Position_LL findPrevious_LL(LinkedList list, DataType_LL data);

/**
 * 向链表之中追加元素
 *
 * @param list 要添加元素的链表
 * @param data 要添加的数据
 */
void add_LL(LinkedList list, DataType_LL data);

/**
 * 向链表中插入数据
 *
 * @param list 要添加数据的链表
 * @param data 指定添加的数据
 * @param pos 指定添加的位置的节点
 */
void insert_LL(LinkedList list, DataType_LL data, Position_LL pos);

/**
 * 根据索引想链表中插入数据
 *
 * @param list 要插入数据的链表
 * @param data 要存放的数据
 * @param index 要插入的索引位置
 */
void insertByIndex_LL(LinkedList list, DataType_LL  data, int index);

/**
 * 清空链表
 *
 * @param list 要被清空的链表
 */
void clear_LL(LinkedList list);

/**
 * 获取头指针
 *
 * @param list 指定链表
 * @return 指定链表的头指针或者头节点
 */
Position_LL header_LL(LinkedList list);

/**
 * 获取链表的第一个元素节点
 *
 * @param list 获取数据的链表
 * @return 链表的第一个数据节点
 */
Position_LL first_LL(LinkedList list);

/**
 * 获取指定位置节点的下一个元素节点
 *
 * @param pos 指定的节点
 * @return 指定节点的下一个节点
 */
Position_LL advance_LL(Position_LL pos);

/**
 * 获取节点的数据
 *
 * @param pos 指定的节点
 * @return 指定节点的数据
 */
DataType_LL dataOfPosNode_LL(Position_LL pos);

/**
 * 根据索引查找元素，将查找的元素存放在Position之中
 *
 * @param list
 * @param index
 * @param pos
 * @return 成功查找则返回true，否则返回false
 */
Position_LL get_LL(LinkedList list, int index);

/**
 * 获取链表中元素的个数
 *
 * @param list 指定链表
 * @return 链表的数据节点的个数
 */
int size_LL(LinkedList list);

/**
 * 显示链表中的数据
 *
 * @param list 指定打印的链表
 */
void showList_LL(LinkedList list);

#endif /* linked_list_h */
