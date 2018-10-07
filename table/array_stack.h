//
//  array_stack.h
//  data-structure
//
//  Created by determination on 2018/9/4.
//  Copyright © 2018年 determination. All rights reserved.
//

#ifndef array_stack_h
#define array_stack_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define STACK_INIT_SIZE 10
#define STACK_INCREASE 10
#define EMPTY_OF_DATA_SBT (-1)

typedef int  DataType_AS;
typedef struct StackRecord{
    int size;
    int top;
    DataType_AS * data;
} ArrayStack, *ArrayStackPtr;

bool initStack_AS(ArrayStackPtr stack);
void makeEmpty_AS(ArrayStackPtr stack);
bool isEmpty_AS(ArrayStackPtr stack);
void pop_AS(ArrayStackPtr stack);
void push_AS(ArrayStackPtr stack, DataType_AS data);
DataType_AS topAndPop_AS(ArrayStackPtr stack);
void clear_AS(ArrayStackPtr stack);
void destroy_AS(ArrayStackPtr stack);
int capacity_AS(ArrayStackPtr stack);
int size_AS(ArrayStackPtr stack);
void showStack_AS(ArrayStackPtr stack);

#endif /* array_stack_h */
