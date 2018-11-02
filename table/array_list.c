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

    list->size = 0;
    list->capacity = MAXSIZE;
    return true;
}

bool clear_AL(ArrayListPtr list) {
    if (!list->data) {
        return false;
    }

    list->size = 0;
    return true;
}

bool destroy_AL(ArrayListPtr *listPtr) {
    if ((*listPtr)->data) {
        free((*listPtr)->data);
        (*listPtr)->size = 0;
        (*listPtr) = NULL;
        return true;
    }

    return false;
}

bool findAndIntoData_AL(ArrayListPtr list, int index, DataType_AL *data) {
    if (index < 1 || index > list->size) {
        printf("out of array index!");
        return false;
    }

    *data = list->data[index - 1];
    return true;
}

DataType_AL get_AL(ArrayListPtr list, int index) {
    if (index < 1 || index > list->size) {
        printf("out of array index!");
        return NULL;
    }

    return list->data[index - 1];
}

bool isExist_AL(ArrayListPtr list, DataType_AL data) {
    if (!list->data) {
        return false;
    }

    for (int i = 0; i < list->size; i++) {
        if (CASE_TYPE (list->data[i]) == CASE_TYPE (data)) return true;
    }

    return false;
}

bool isEmpty_AL(ArrayListPtr list) {
    return list->size == 0;
}


bool add_AL(ArrayListPtr list, DataType_AL data) {
    if (list->size == list->capacity) {
        DataType_AL *newData = (DataType_AL *) realloc(list->data,
                                                       (list->capacity + INCREMENT) * sizeof(DataType_AL));
        assert(newData);

        list->data = newData;
        list->capacity += INCREMENT;
    }

    list->data[list->size] = data;
    list->size++;
    return true;
}

bool insert_AL(ArrayListPtr list, int index, DataType_AL data) {
    DataType_AL *newData;

    if (index < 1 || index > list->size + 1)   // 只能插入第一个位置和顺序表尾部
    {
        printf("out of array index!");
        return false;
    }

    if (list->size == list->capacity)   // 如果当前元素个数等于最大容量，则需要扩容
    {
        newData = (DataType_AL *) realloc(list->data,
                                          (list->capacity + INCREMENT) * sizeof(DataType_AL));
        assert(newData);

        list->data = newData;
        list->capacity += INCREMENT;
    }

    // 执行元素后移
    for (int i = list->size - 1; i >= index - 1; i--) {
        list->data[i + 1] = list->data[i];
    }

    list->data[index - 1] = data;
    list->size++;
    return true;
}

bool remove_AL(ArrayListPtr list, int index, DataType_AL *data) {
    if (index < 1 || index > list->size) {
        printf("out of array index !");
        return false;
    }

    *data = list->data[index - 1];

    // 执行操作前移
    for (int i = index - 1; i < list->size; i++) {
        list->data[i] = list->data[i + 1];
    }

    list->size--;
    return true;
}


void showList_AL(ArrayListPtr list) {
    if (!list) return;

    int i = 0;
    while (i < list->size) {
        PRINT_FMT(list->data[i]);
        i++;
    }
    printf("\n\n");
}

int size_AL(ArrayListPtr list) {
    assert(list);
    return list->size;
}

int capacity_AL(ArrayListPtr list) {
    assert(list);
    return list->capacity;
}


ArrayListPtr merge_AL(ArrayListPtr one, ArrayListPtr another) {
    ArrayListPtr resultList = newArrayList();

    copyToResultList_AL(one, resultList);
    copyToResultList_AL(another, resultList);
    return resultList;
}

void copyToResultList_AL(ArrayListPtr sourceList, ArrayListPtr resultList) {
    assert(sourceList);
    assert(resultList);

    for (int i = 0; i < sourceList->size; i++) {
        add_AL(resultList, sourceList->data[i]);
    }
}

bool union_AL(ArrayListPtr one, ArrayListPtr another) {
    assert(one);

    if (another == NULL) {
        fputs("要合并的顺序表为NULL", stderr);
        return false;
    }

    copyToResultList_AL(another, one);
    return true;
}

DataType_AL previous_AL(ArrayListPtr list, int pos) {
    assert(list);
    assert(pos >= 2 && pos <= list->size);

    int currentPos = pos - 1;
    return list->data[currentPos - 1];
}

DataType_AL advance_AL(ArrayListPtr list, int pos) {
    assert(list);
    assert(pos >= 1 && pos < list->size);

    return list->data[pos];
}

