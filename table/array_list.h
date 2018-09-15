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
    int length;
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

#endif /* array_list_h */
