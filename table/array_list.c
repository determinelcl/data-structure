//
//  array_list.c
//  data-structure
//
//  Created by determination on 2018/8/25.
//  Copyright © 2018年 determination. All rights reserved.
//

#include "array_list.h"

/**
 * 初始化构造一个空顺序表
 */
bool newArrayList(ArrayListPtr arrayListPtr)   //参数类型为指针变量
{
    // 指针变量结构体引用成员变量使用->运算符;
    // malloc函数申请的内存返回值要强转成对应存储格式的指针类型
    arrayListPtr->data = (DataType_AL *) malloc(MAXSIZE * sizeof(DataType_AL));
    
    if(arrayListPtr->data == NULL)
    {
        printf("内存空间不足！");
        return false;
    }
    
    arrayListPtr->length = 0;
    arrayListPtr->capacity = MAXSIZE;
    return true;
}

/**
 * 重置为空表；初始条件：顺序表存在
 */
bool clear_AL(ArrayListPtr arrayListPtr)
{
    if(!arrayListPtr->data)
    {
        return false;
    }
    
    arrayListPtr->length = 0;
    return true;
}

/**
 * 销毁顺序表，回收内存空间；初始条件：顺序表存在
 */
bool destory_AL(ArrayListPtr arrayListPtr)
{
    if (arrayListPtr->data)
    {
        free(arrayListPtr->data);
        arrayListPtr->length=0;
        arrayListPtr = NULL;
        printf("destroy succeed!");
        return true;
    }
    
    return false;
}

/**
 * 根据索引返回元素
 */
bool get_AL(ArrayListPtr arrayListPtr, int index, DataType_AL* data)
{
    if (index < 1 || index > arrayListPtr->length)
    {
        printf("out of array index!");
        return false;
    }
    
    *data = arrayListPtr->data[index - 1];
    return true;
}

/**
 * 查找某个元素是否存在
 */
bool isExist_AL(ArrayListPtr arrayListPtr, DataType_AL data)
{
    if(!arrayListPtr->data)
    {
        return false;
    }
    
    int i = 0;
    while(i < arrayListPtr->length)
    {
        if(arrayListPtr->data[i] == data)
        {
            return true;
        }
        i++;
    }
    
    return false;
}

/**
 * 判空
 */
bool isEmpty_AL(ArrayListPtr arrayListPtr)
{
    return arrayListPtr->length == 0;
}



/**
 * 添加元素到列表末尾
 */
bool add_AL(ArrayListPtr arrayListPtr, DataType_AL data)
{
    if (arrayListPtr->length == arrayListPtr->capacity)
    {
        DataType_AL *newData = (DataType_AL *) realloc(arrayListPtr->data, (arrayListPtr->capacity + INCREMENT) * sizeof(DataType_AL));
        if (newData ==  NULL)
        {
            printf("内存空间不足！");
            return false;
        }
        
        arrayListPtr->data = newData;
        arrayListPtr->capacity += INCREMENT;
    }
    
    arrayListPtr->data[arrayListPtr->length] = data;
    arrayListPtr->length++;
    return true;
}

/**
 * 插入元素到指定位置
 */
bool insert_AL(ArrayListPtr arrayListPtr, int index, DataType_AL data)
{
    DataType_AL* newData;
    
    if(index < 1 || index > arrayListPtr->length + 1)   //只能插入第一个位置到当前元素个数+1这之间的位置
    {
        printf("out of array index!");
        return false;
    }
    
    if(arrayListPtr->length == arrayListPtr->capacity)   //如果当前元素个数等于表长，则需要扩容
    {
        newData = (DataType_AL *) realloc(arrayListPtr->data, (arrayListPtr->capacity + INCREMENT) * sizeof(DataType_AL));
        if (newData ==  NULL)
        {
            printf("内存空间不足！");
            return false;
        }
        
        arrayListPtr->data = newData; //要将新首地址赋值给arrayList->data
        arrayListPtr->capacity += INCREMENT; //表长增加
    }
    
    for(int i = arrayListPtr->length - 1; i >= index - 1; i--)
    {
        arrayListPtr->data[i + 1] = arrayListPtr->data[i]; //后移操作
    }
    
    arrayListPtr->data[index - 1] = data; //插入操作
    arrayListPtr->length++;
    return true;
}

/**
 * 删除指定位置元素，并用e返回
 */
bool remove_AL(ArrayListPtr arrayListPtr, int index, DataType_AL* data)
{
    if(index < 1 || index > arrayListPtr->length)
    {
        printf("out of array index !");
        return false;
    }
    
    *data = arrayListPtr->data[index - 1];
    
    for(int i = index - 1; i < arrayListPtr->length; i++)
    {
        arrayListPtr->data[i] = arrayListPtr->data[i + 1];//前移操作
    }
    
    arrayListPtr->length--;
    return true;
}

/**
 * 遍历顺序表
 */
void showList_AL(ArrayListPtr arrayListPtr)
{
    int i = 0;
    printf("\n顺序表表长 = %d, 元素个数 = %d,其元素分别为：\n\t", arrayListPtr->capacity, arrayListPtr->length);
    while(i < arrayListPtr->length)
    {
        printf("%d\t", arrayListPtr->data[i]);
        i++;
    }
    printf("\n");
}
