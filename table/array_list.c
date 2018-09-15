//
//  array_list.c
//  data-structure
//
//  Created by determination on 2018/8/25.
//  Copyright © 2018年 determination. All rights reserved.
//

#include "array_list.h"

#define CASE_TYPE *(int*)
#define PRINT_FMT(data) printf("%d\t", CASE_TYPE (data));

ArrayListPtr newArrayList() {
    ArrayListPtr list = malloc(sizeof(ArrayList));
    assert(list);

    initArrayList(list);
    return list;
}

bool initArrayList(ArrayListPtr list) {
    list->data = (DataType_AL *) malloc(MAXSIZE * sizeof(DataType_AL));

    assert(list->data);

    list->length = 0;
    list->capacity = MAXSIZE;
    return true;
}

bool clear_AL(ArrayListPtr list) {
    if (!list->data) {
        return false;
    }

    list->length = 0;
    return true;
}

bool destroy_AL(ArrayListPtr *listPtr) {
    if ((*listPtr)->data) {
        free((*listPtr)->data);
        (*listPtr)->length = 0;
        (*listPtr) = NULL;
        return true;
    }

    return false;
}

bool findAndIntoData_AL(ArrayListPtr list, int index, DataType_AL *data) {
    if (index < 1 || index > list->length) {
        printf("out of array index!");
        return false;
    }

    *data = list->data[index - 1];
    return true;
}

DataType_AL get_AL(ArrayListPtr list, int index) {
    if (index < 1 || index > list->length) {
        printf("out of array index!");
        return NULL;
    }

    return list->data[index-1];
}

bool isExist_AL(ArrayListPtr list, DataType_AL data) {
    if (!list->data) {
        return false;
    }

    int i = 0;
    while (i < list->length) {
        if (list->data[i] == data) {
            return true;
        }
        i++;
    }

    return false;
}

bool isEmpty_AL(ArrayListPtr list) {
    return list->length == 0;
}


bool add_AL(ArrayListPtr list, DataType_AL data) {
    if (list->length == list->capacity) {
        DataType_AL *newData = (DataType_AL *) realloc(list->data,
                                                       (list->capacity + INCREMENT) * sizeof(DataType_AL));
        assert(newData);

        list->data = newData;
        list->capacity += INCREMENT;
    }

    list->data[list->length] = data;
    list->length++;
    return true;
}

bool insert_AL(ArrayListPtr list, int index, DataType_AL data) {
    DataType_AL *newData;

    if (index < 1 || index > list->length + 1)   // 只能插入第一个位置和顺序表尾部
    {
        printf("out of array index!");
        return false;
    }

    if (list->length == list->capacity)   // 如果当前元素个数等于最大容量，则需要扩容
    {
        newData = (DataType_AL *) realloc(list->data,
                                          (list->capacity + INCREMENT) * sizeof(DataType_AL));
        assert(newData);

        list->data = newData;
        list->capacity += INCREMENT;
    }

    // 执行元素后移
    for (int i = list->length - 1; i >= index - 1; i--) {
        list->data[i + 1] = list->data[i];
    }

    list->data[index - 1] = data;
    list->length++;
    return true;
}

bool remove_AL(ArrayListPtr list, int index, DataType_AL *data) {
    if (index < 1 || index > list->length) {
        printf("out of array index !");
        return false;
    }

    *data = list->data[index - 1];

    for (int i = index - 1; i < list->length; i++) {
        list->data[i] = list->data[i + 1];// 前移操作
    }

    list->length--;
    return true;
}


void showList_AL(ArrayListPtr list) {
    if (!list) return;

    int i = 0;
    while (i < list->length) {
        PRINT_FMT(list->data[i]);
        i++;
    }
    printf("\n\n");
}

int size_AL(ArrayListPtr list) {
    assert(list);
    return list->length;
}

int capacity_AL(ArrayListPtr list) {
    assert(list);
    return list->capacity;
}
