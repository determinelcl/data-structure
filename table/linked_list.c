//
//  linked_list.c
//  data-structure
//
//  Created by determination on 2018/8/26.
//  Copyright © 2018年 determination. All rights reserved.
//

#include "linked_list.h"

#define CASE_TYPE *(int *)
#define PRINT_FMT(data) printf("%d\t", CASE_TYPE (data))

LinkedList newLinkedList() {
    LinkedList list = malloc(sizeof(struct Node));
    assert(list != NULL);

    list->next = NULL;
    return list;
}

bool isEmpty_LL(LinkedList list) {
    return list->next == NULL;
}

// 判断两个指针是否相等
bool equalsOfPtr_LL(const Position_LL pos, const Position_LL temp) {
    return temp && temp == pos && temp->next == NULL;
}

bool isLast_LL(LinkedList list, Position_LL pos) {
    assert(list != NULL);

    Position_LL temp = list->next;
    while (temp) {
        if (equalsOfPtr_LL(pos, temp)) return true;
        temp = temp->next;
    }

    return false;
}

bool isHead_LL(LinkedList list, Position_LL pos) {
    return list == pos;
}

// 用于比较两个数据类型，转换之后的值
static bool equals_LL(DataType_LL one, DataType_LL another) {
    return CASE_TYPE one == CASE_TYPE another;
}

Position_LL find_LL(LinkedList list, DataType_LL data) {
    Position_LL pos;
    pos = list->next;
    while (pos && !equals_LL(pos->data, data)) {
        pos = pos->next;
    }

    return pos;
}

void delete_LL(LinkedList list, DataType_LL data) {
    assert(list != NULL);
    if (isEmpty_LL(list)) return;

    Position_LL prev = findPrevious_LL(list, data);

    if (prev != NULL) {
        Position_LL tempCell = prev->next;
        prev->next = tempCell->next;
        free(tempCell);
    }
}

Position_LL findPrevious_LL(LinkedList list, DataType_LL data) {

    Position_LL pos = list;
    while (pos->next && !equals_LL(pos->next->data, data))
        pos = pos->next;

    return pos;
}

void add_LL(LinkedList list, DataType_LL data) {
    Position_LL pos = list;

    while (pos->next) {
        pos = pos->next;
    }

    Position_LL tempCell = malloc(sizeof(struct Node));
    assert(tempCell != NULL);

    tempCell->data = data;
    tempCell->next = NULL;
    pos->next = tempCell;
}

// 检查元素节点是否属于链表
static bool isBelongToList(LinkedList list, Position_LL pos) {
    Position_LL temp = list;

    while (temp) {
        if (temp == pos) return true;
        temp = temp->next;
    }

    return false;
}

void insert_LL(LinkedList list, DataType_LL data, Position_LL pos) {
    assert(list);
    assert(pos);
    assert(isBelongToList(list, pos));

    Position_LL tempCell = malloc(sizeof(struct Node));

    assert(tempCell != NULL);

    tempCell->data = data;
    tempCell->next = pos->next;
    pos->next = tempCell;
}

void insertByIndex_LL(LinkedList list, DataType_LL data, int index) {
    assert(list != NULL);

    Position_LL pos = list;

    int count = 1;
    while (pos) {
        if (count == index || !pos->next) {
            Position_LL tempCell = malloc(sizeof(struct Node));
            assert(tempCell != NULL);

            tempCell->data = data;
            tempCell->next = pos->next;
            pos->next = tempCell;
            break;
        }

        count++;
        pos = pos->next;
    }
}

void clear_LL(LinkedList list) {
    Position_LL pos, temp;
    pos = list->next;
    list->next = NULL;

    while (pos) {
        temp = pos->next;
        free(pos);
        pos = temp;
    }
}

Position_LL header_LL(LinkedList list) {
    return list;
}

Position_LL first_LL(LinkedList list) {
    return list->next;
}

Position_LL advance_LL(Position_LL pos) {
    return pos ? pos->next : pos;
}

DataType_LL dataOfPosNode_LL(Position_LL pos) {
    return pos->data;
}

Position_LL get_LL(LinkedList list, int index) {
    Position_LL pos = list->next;
    int i = 1;

    while (pos && i < index) {
        pos = pos->next;
        i++;
    }

    return pos ? pos : NULL;
}


int size_LL(LinkedList list) {
    int size = 0;

    Position_LL temp;
    temp = list->next;

    while (temp) {
        temp = temp->next;
        size++;
    }
    return size;
}

void showList_LL(LinkedList list) {
    if (!list) return;

    Position_LL pos;
    pos = list->next;

    while (pos) {
        PRINT_FMT(pos->data);
        pos = pos->next;
    }

    printf("\n\n");
}













