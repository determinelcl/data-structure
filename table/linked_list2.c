//
//  linked_list2.c
//  data-structure
//
//  Created by determination on 2018/8/26.
//  Copyright © 2018年 determination. All rights reserved.
//

#include "linked_list2.h"

// 创建一个链表 成功返回该链表的指针 否则返回NULL
LinkedList2 newLinkedList2( void )
{
    // 创建一个新节点
    LinkedList2 list = (LinkedList2) malloc(sizeof(List_LL2));
    // 创建不成功，返回NULL
    if(!list) return NULL;
    
    list->head = NULL;
    list->tail = NULL;
    list->curr = NULL;
    list->size = 0;
    
    // 初始化成功后，返回list
    return list;
}

// 将元素添加到链表的末尾，成功返回链表的size，失败返回-1
int addBack_LL2(LinkedList2 list, DataType_LL2 data)
{
    // 创建一个新节点，创建不成功的话，返回-1
    Position_LL2 node = (Position_LL2) malloc(sizeof(Node_LL2));
    if(!node) return -1;
    
    // 为节点的数据域赋值
    node->data = data;
    // 如果为链表的末尾
    if(list->tail)
    {
        list->tail->next = node;         // 把新节点赋给链表末尾的下一个
        node->prev       = list->tail;   // 新节点的前一个等于之前的末节点
        node->next       = NULL;         // 新节点为末节点，把它下一个指向NULL
    }
    else // 如果不为末尾，其实就是空链表
    {
        node->next       = NULL;         // 新节点的下一个为NULL
        node->prev       = NULL;         // 新节点的前一个为NULL
        list->head       = node;         // 链表的头为新节点node
    }
    list->tail = node;                   // 链表的末尾指向node
    
    return ++list->size;                 // 返回链表的size
}

// 将元素添加到链表前端，成功返回非0，否则返回0
int addFront_LL2(LinkedList2 list, DataType_LL2 data)
{
    Position_LL2 node = (Position_LL2)malloc(sizeof(Node_LL2));
    if(!node) return 0;
    
    node->data = data;
    if(list->head)
    {
        list->head->prev = node;
        node->next       = list->head;
        node->prev       = NULL;
    }
    else
    {
        node->next       = NULL;
        node->prev       = NULL;
        list->tail       = node;
    }
    list->head = node;
    
    return ++list->size;
}

// 将元素从末端移除并返回该元素，如果链表为空则返回NULL
DataType_LL2 removeBack_LL2(LinkedList2 list)
{
    Position_LL2 temp;
    DataType_LL2 data;
    
    if(!list->size) return NULL;
    
    temp = list->tail;
    data = list->tail->data;
    
    if(list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
        list->curr  = NULL;
    }
    else
    {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    --list->size;
    free(temp);
    return data;
}

// 将元素从前端移除并返回该元素，如果链表为空则返回NULL
DataType_LL2 removeFront_LL2(LinkedList2 list)
{
    Position_LL2 temp;
    DataType_LL2 data;
    
    if(!list->size) return NULL;
    
    temp = list->head;
    data = list->head->data;
    
    if(list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
        list->curr  = NULL;
    }
    else
    {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    --list->size;
    free(temp);
    return data;
}

/* 如果当前链表为空则返回非0，否则返回0 */
int isEmpty_LL2(LinkedList2 list)
{
    return list->size == 0;
}

/* 获得链表的大小（元素总个数） */
int size_LL2(LinkedList2 list)
{
    return list->size;
}

/* 将当前位置移动到链表的开始 */
void begin_LL2(LinkedList2 list)
{
    list->curr = list->head;
}

/* 将当前位置移动到链表的最后 */
void end_LL2(LinkedList2 list)
{
    list->curr = list->tail;
}
/* 将当前位置向后移动一个位置 */
void moveNext_LL2(LinkedList2 list)
{
    list->curr = list->curr->next;
}

/* 将当前位置向后移动一个位置 */
void movePrev_LL2(LinkedList2 list)
{
    list->curr = list->curr->prev;
}

/* 清空链表中所有元素 */
void clear_LL2(LinkedList2 list)
{
    while(removeBack_LL2(list));
}

/* 销毁一个链表 */
void destroy_LL2(LinkedList2 list)
{
    clear_LL2(list);
    free(list);
}

/* 如果当前位置之后还有元素则返回非0，否则返回0 */
int hasNext_LL2(LinkedList2 list)
{
    if (!list->curr) return 0;
    if (list->curr == list->tail) return 1;
    return list->curr->next != NULL;
}

/* 如果当前位置之前还有元素则返回非0，否则返回0 */
int hasPrev_LL2(LinkedList2 list)
{
    if (!list->curr) return 0;
    if (list->curr == list->head) return 1;
    return list->curr->prev != NULL;
}

/* 返回当前位置的元素 */
DataType_LL2 current_LL2(LinkedList2 list)
{
    return list->curr->data;
}



// 正向打印链表
void traverse_LL2(LinkedList2 list)
{
    for( begin_LL2(list); hasNext_LL2(list); moveNext_LL2(list) )
        printf("%d ", *(int*)current_LL2(list));
    putchar('\n');
}

// 反向打印链表
void rTraverse_LL2(LinkedList2 list)
{
    for (end_LL2(list); hasPrev_LL2(list); movePrev_LL2(list))
        printf("%d ", *(int*)current_LL2(list));
    putchar('\n');
}

