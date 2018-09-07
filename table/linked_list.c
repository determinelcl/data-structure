//
//  linked_list.c
//  data-structure
//
//  Created by determination on 2018/8/26.
//  Copyright © 2018年 determination. All rights reserved.
//

#include "linked_list.h"

bool newLinkedList(LinkedList list)
{
    list = malloc(sizeof(struct Node));
    if (list == NULL) {
        printf("内存空间不足！");
        return false;
    }
    
    list->next = NULL;
    return true;
}

bool isEmpty_LL(LinkedList list)
{
    return list->next == NULL;
}

bool isLast_LL(Position_LL pos, LinkedList list)
{
    return pos->next == NULL;
}

Position_LL find_LL(DataType_LL data, LinkedList list)
{
    Position_LL pos;
    pos = list->next;
    while (pos != NULL && pos->data != data) {
        pos = pos->next;
    }
    return pos;
}

void delete_LL(DataType_LL data, LinkedList list)
{
    Position_LL pos, tempCell;
    pos = list->next;
    
    Position_LL prev = findPrevious_LL(data, list);
    if (!isLast_LL(prev, list)) {
        tempCell = prev->next;
        prev->next = tempCell->next;
        free(tempCell);
    }
}

Position_LL findPrevious_LL(DataType_LL data, LinkedList list)
{
    Position_LL pos;
    pos = list;
    while (pos->next != NULL && pos->next->data != data)
        pos = pos->next;
    
    return pos;
}

void add_LL(DataType_LL data, LinkedList list, Position_LL pos)
{
    Position_LL tempCell;
    tempCell = malloc(sizeof(struct Node));
    
    if (tempCell) {
        printf("内存空间不足！");
        return;
    }
    
    tempCell->data = data;
    tempCell->next = pos->next;
    pos->next = tempCell;
}

void clear_LL(LinkedList list)
{
    Position_LL pos, temp;
    pos = list->next;
    list->next = NULL;
    
    while (pos != NULL) {
        temp = pos->next;
        free(pos);
        pos = temp;
    }
}

Position_LL header_LL(LinkedList list)
{
    return list;
}

Position_LL first_LL(LinkedList list)
{
    return list->next;
}

Position_LL advance_LL(Position_LL pos)
{
    return !pos ? pos->next : pos;
}

DataType_LL retrieve_LL(Position_LL pos)
{
    return pos->data;
}

bool get_LL(LinkedList list, int index, Position_LL pos)
{
    pos = list->next;
    int i = 1;
    
    while (pos && i < index) {
        pos = pos->next;
        i++;
    }
    
    if (!pos || i > index)
        return false;
    
    return true;
}


int size_LL(LinkedList list)
{
    int size = 0;
    
    Position_LL temp;
    temp = list->next;
    
    while (temp) {
        temp = temp->next;
        size++;
    }
    return size;
}

void showList_LL(LinkedList list)
{
    if (!list) return;
    
    Position_LL pos;
    pos = list->next;
    
    while (pos) {
        printf("%-10d", pos->data);
        pos = pos->next;
    }
}













