//
//  linked_list2.h
//  data-structure
//
//  Created by determination on 2018/8/26.
//  Copyright © 2018年 determination. All rights reserved.
//

#ifndef linked_list2_h
#define linked_list2_h

#include <stdio.h>
#include <stdlib.h>

typedef int* DataType_LL2;
typedef struct NodeTag Node_LL2, *Position_LL2;
typedef struct LinkedListTag List_LL2, *LinkedList2;

struct NodeTag
{
    Position_LL2 prev;
    Position_LL2 next;
    DataType_LL2 data;
};

struct LinkedListTag
{
    Position_LL2 head;
    Position_LL2 tail;
    Position_LL2 curr;
    int size;
};


// 创建一个链表 成功返回该链表的指针 否则返回NULL
LinkedList2 newLinkedList2( void );

// 将元素添加到链表的末尾，成功返回链表的size，失败返回-1
int addBack_LL2(LinkedList2 list, DataType_LL2 data);

// 将元素添加到链表前端，成功返回非0，否则返回0
int addFront_LL2(LinkedList2 list, DataType_LL2 data);

// 将元素从末端移除并返回该元素，如果链表为空则返回NULL
DataType_LL2 removeBack_LL2(LinkedList2 list);

// 将元素从前端移除并返回该元素，如果链表为空则返回NULL
DataType_LL2 removeFront_LL2(LinkedList2 list);

/* 如果当前链表为空则返回非0，否则返回0 */
int isEmpty_LL2(LinkedList2 list);

/* 获得链表的大小（元素总个数） */
int size_LL2(LinkedList2 list);

/* 将当前位置移动到链表的开始 */
void begin_LL2(LinkedList2 list);

/* 将当前位置移动到链表的最后 */
void end_LL2(LinkedList2 list);

/* 将当前位置向后移动一个位置 */
void moveNext_LL2(LinkedList2 list);

/* 将当前位置向后移动一个位置 */
void movePrev_LL2(LinkedList2 list);

/* 清空链表中所有元素 */
void clear_LL2(LinkedList2 list);

/* 销毁一个链表 */
void destroy_LL2(LinkedList2 list);

/* 如果当前位置之后还有元素则返回非0，否则返回0 */
int hasNext_LL2(LinkedList2 list);

/* 如果当前位置之前还有元素则返回非0，否则返回0 */
int hasPrev_LL2(LinkedList2 list);

/* 返回当前位置的元素 */
DataType_LL2 current_LL2(LinkedList2 list);

// 正向打印链表
void traverse_LL2(LinkedList2 list);

// 反向打印链表
void rTraverse_LL2(LinkedList2 list);

#endif /* linked_list2_h */
