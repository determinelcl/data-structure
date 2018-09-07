//
//  linked_list_o.c
//  data-structure
//
//  Created by determination on 2018/8/28.
//  Copyright © 2018年 determination. All rights reserved.
//

#include "linked_list_o.h"

Criculist newLinkedListO(void)
{
    Position_LLO head;
    head = (Criculist) malloc(LEN);
    
    if (NULL == head)
        printf("内存空间不足！");
    
    head->data = 0;
    head->next = head;
    
    return head;
}

Position_LLO find_LLO(Criculist list, int index)
{
    Position_LLO prev;
    prev = list->next;
    
    int j = 1;
    while ((prev->next != list) && (j < index))
    {
        prev = prev->next;
        j++;
    }
    
    return prev;
}

Position_LLO findPrevious_LLO(DataType_LLO data, Criculist list)
{
    Position_LLO pos;
    pos = list;
    while (pos->next != NULL && *pos->next->data != *data)
        pos = pos->next;
    
    return pos;
}

Position_LLO add_LLO(Criculist list,  DataType_LLO data)
{
    Position_LLO pos, tail = list, newObj = NULL;
    pos = list->next;
    
    while (pos != list) {
        tail = pos;
        pos = pos->next;
    }
    
    newObj = (Position_LLO) malloc(LEN);
    newObj->data = data;
    newObj->next = list;
    tail->next = newObj;
    
    return newObj;
}

void insert_LLO(Criculist list, int pos, DataType_LLO data)
{
    Position_LLO prev = find_LLO(list, pos);
    Position_LLO ptr = (Position_LLO) malloc(LEN);
    
    if (NULL == ptr)
        printf("内存空间不足！");
    
    ptr->data = data;
    ptr->next = prev->next;
    prev->next = ptr;
}

void delete_LLO(Criculist list, int index, DataType_LLO data)
{
    Position_LLO curr, prev;
    curr = find_LLO(list, index);
    prev = findPrevious_LLO(curr->data, list);
    
    *data = *curr->data;
    prev->next = curr->next;
    
    free(curr);
}

int indexOf_LLO(Criculist list, DataType_LLO data)
{
    Position_LLO prev = list->next;
    
    int index = 1;
    while ((prev != list) && (*prev->data != *data))
    {
        prev = prev->next;
        index++;
    }
    
    return index;
}

int size_LLO(Criculist list)
{
    Position_LLO prev = list->next;
    int length = 0;
    while (prev != list)
    {
        prev = prev->next;
        length++;
    }
    
    return length;
}

void showList_LLO(Criculist list)
{
    Position_LLO prev = list->next;
    printf("链表的数据是：");
    while (prev != list)
    {
        printf("%d \t", *prev->data);
        prev = prev->next;
    }
    printf("\n");
}
