//
//  array_list.h
//  data-structure
//
//  Created by determination on 2018/8/25.
//  Copyright © 2018年 determination. All rights reserved.
//

#ifndef array_list_h
#define array_list_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int DataType_AL;

typedef struct  //顺序表三要素：元素基址、元素个数、表长
{
    DataType_AL * data; //数据元素基址
    int length; //顺序表当前元素个数
    int capacity; //顺序表表长
} ArrayList, *ArrayListPtr; //顺序表三要素：元素基址、元素个数、表长

#define MAXSIZE 10
#define INCREMENT 10

/**
 * 初始化构造一个空顺序表
 */
bool newArrayList(ArrayListPtr arrayListPtr);

/**
 * 重置为空表；初始条件：顺序表存在
 */
bool clear_AL(ArrayListPtr arrayListPtr);

/**
 * 销毁顺序表，回收内存空间；初始条件：顺序表存在
 */
bool destory_AL(ArrayListPtr arrayListPtr);

/**
 * 根据位序返回元素
 * 思考：为什么要将返回结果作为参数传递进去而不是直接利用函数返回值传递？
 * 答：为了使函数更具有通用性，适应性更高，因为执行函数的结果有可能是正常返回指定的元素值，
 * 有可能查询失败而返回失败信息，此时如果用返回值类型做为函数返回值那么可能需要借助一些特殊值来区分失败的情况
 */
bool get_AL(ArrayListPtr arrayListPtr, int pos, DataType_AL* data);

/**
 * 查找某个元素是否存在
 */
bool isExist_AL(ArrayListPtr arrayListPtr, DataType_AL data);

/**
 * 判空
 */
bool isEmpty_AL(ArrayListPtr arrayListPtr);

/**
 * 添加元素到列表末尾
 */
bool add_AL(ArrayListPtr arrayListPtr, DataType_AL data);

/**
 * 插入元素到指定位置
 */
bool insert_AL(ArrayListPtr arrayListPtr, int pos, DataType_AL data);

/**
 * 删除指定位置元素，并用e返回
 */
bool remove_AL(ArrayListPtr arrayListPtr, int pos, DataType_AL* data);

/**
 * 遍历顺序表
 */
void showList_AL(ArrayListPtr arrayListPtr);

#endif /* array_list_h */
