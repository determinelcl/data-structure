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
#include <assert.h>

typedef void *DataType_AL;

typedef struct {
    DataType_AL *data;
    int size;
    int capacity;
} ArrayList, *ArrayListPtr;

#define MAXSIZE 10
#define INCREMENT 10


/**
 * 构造一个新的顺序表
 *
 * @return 新的顺序表
 */
ArrayListPtr newArrayList(void);

/**
 * 初始化一个顺序表，
 *
 * @param list 顺序表的指针
 * @return 返回初始化结果
 */
bool initArrayList(ArrayListPtr list);

/**
 * 清空顺序表中的元素
 *
 * @param list 指向顺序表的指针
 * @return 清空是否成功
 */
bool clear_AL(ArrayListPtr list);

/**
 * 销毁顺序表，由于传递的是指针，释放完成内存之后
 * 要置指向被释放内存的引用为空，所以需要传递二级指针
 *
 * @param listPtr 执行顺序表指针的指针
 * @return 销毁是否成功
 */
bool destroy_AL(ArrayListPtr *listPtr);

/**
 * 根据索引查询元素
 *
 * @param list 要查询的顺序表的指针
 * @param index 索引位置
 * @param data 查找到的数据将会存放在数据指针里
 * @return 操作是否完成
 */
bool findAndIntoData_AL(ArrayListPtr list, int index, DataType_AL *data);

/**
 * 根据索引查询元素，并返回
 *
 * @param list 要查询的顺序表的指针
 * @param index 索引位置
 * @return 找到返回数据元素，否则返回NULL
 */
DataType_AL get_AL(ArrayListPtr list, int index);

/**
 * 判断指定元素是否在指定列表中
 *
 * @param list 顺序表指针
 * @param data 要判断是否存在的数据
 * @return
 */
bool isExist_AL(ArrayListPtr list, DataType_AL data);

/**
 * 判断顺序表是否为空
 *
 * @param list 顺序表指针
 * @return 为空返回true，否则返回false
 */
bool isEmpty_AL(ArrayListPtr list);

/**
 * 添加元素
 *
 * @param list 顺序表
 * @param data 要添加的数据
 * @return 返回操作是否成功
 */
bool add_AL(ArrayListPtr list, DataType_AL data);

/**
 * 向顺序表中插入元素
 *
 * @param list 顺序表
 * @param index 指定插入的索引位置
 * @param data 插入的数据
 * @return 操作是否成功
 */
bool insert_AL(ArrayListPtr list, int index, DataType_AL data);

/**
 * 删除指定索引位置的元素
 *
 * @param list 顺序表指针
 * @param index 指定删除的索引位置
 * @param data 删除的数据将会存放着data里面
 * @return 操作是否成功
 */
bool remove_AL(ArrayListPtr list, int index, DataType_AL *data);

/**
 * 显示顺序表中的所有元素
 *
 * @param list 顺序表
 */
void showList_AL(ArrayListPtr list);

/**
 * 获取顺序表中元素的个数
 *
 * @param list 顺序表
 * @return 顺序表的个数
 */
int size_AL(ArrayListPtr list);

/**
 * 获取顺序表的容量
 *
 * @param list 顺序表
 * @return 顺序表的容量
 */
int capacity_AL(ArrayListPtr list);

/**
 * 将一个顺序表的元素拷贝到一个新的顺序表
 *
 * @param sourceList 源顺序表，将要被拷贝的顺序表
 * @param resultList 目标顺序表，新的顺序表
 */
void copyToResultList_AL(ArrayListPtr sourceList, ArrayListPtr resultList);

/**
 * 合并两个顺序表，并将新的顺序表返回
 *
 * @param one 第一个顺序表
 * @param another 第二个合并的顺序表
 * @return 合并之后的顺序表
 */
ArrayListPtr merge_AL(ArrayListPtr one, ArrayListPtr another);

/**
 * 将第二个顺序表的数据放入到第一个顺序表之中，称之为合并顺序表
 *
 * @param one 第一个顺序表将会改变并包含第二个顺序表
 * @param another 第二个顺序表将被合并的顺序表
 * @return 合并成功返回true，否则返回true
 */
bool union_AL(ArrayListPtr one, ArrayListPtr another);

/**
 * 获取指定位置的前面一个位置的数据元素
 *
 * @param list 获取数据的顺序表
 * @param pos 指定获取前驱元素的索引
 * @return 指定索引位置的数据元素的前驱元素
 */
DataType_AL previous_AL(ArrayListPtr list, int pos);


/**
 * 获取指定索引位置的下一个数据元素
 *
 * @param list 指定获取元素的顺序表
 * @param pos 指定获取后继元素的索引
 * @return 指定索引位置的数据元素的后继元素
 */
DataType_AL advance_AL(ArrayListPtr list, int pos);

#endif /* array_list_h */
