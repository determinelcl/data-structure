//
//  array_stack.c
//  data-structure
//
//  Created by determination on 2018/9/4.
//  Copyright © 2018年 determination. All rights reserved.
//

#include "array_stack.h"


bool initStack_AS(ArrayStackPtr stack)
{
    stack->data = (DataType_AS *) malloc(sizeof(DataType_AS) * STACK_INIT_SIZE);
    if (!stack->data) {
        printf("内存空间不足！");
        return false;
    }
    makeEmpty_AS(stack);
    stack->size = STACK_INIT_SIZE;
    return true;
}

void makeEmpty_AS(ArrayStackPtr stack)
{
    stack->top = EMPTY_OF_DATA;
}

bool isEmpty_AS(ArrayStackPtr stack)
{
    return stack->top == EMPTY_OF_DATA;
}

void pop_AS(ArrayStackPtr stack)
{
    if (isEmpty_AS(stack)) {
        printf("栈为空，无法弹出任何元素");
        return;
    }
    
    stack->top--;
}

void push_AS(ArrayStackPtr stack, DataType_AS data)
{
    if (stack->top == (stack->size - 1)) {
        stack->data = (DataType_AS *) realloc(stack->data, (stack->size + STACK_INCREASE) * sizeof(DataType_AS));
        
        if (!stack->data) {
            printf("内存分配失败！");
            return;
        }
        
        stack->size += STACK_INCREASE;
    }
    
    stack->data[++stack->top] = data;
}

DataType_AS topAndPop_AS(ArrayStackPtr stack)
{
    if (isEmpty_AS(stack)) {
        printf("栈为空，无法弹出任何元素");
        return -1;
    }
    
    return stack->data[stack->top--];
}

void clear_AS(ArrayStackPtr stack)
{
    makeEmpty_AS(stack);
}

void destroy_AS(ArrayStackPtr stack)
{
    if (stack) {
        free(stack->data);
        free(stack);
    }
}

int capacity_AS(ArrayStackPtr stack)
{
    return stack->size;
}

int size_AS(ArrayStackPtr stack)
{
    return stack->top + 1;
}

void showStack_AS(ArrayStackPtr stack)
{
    int count = stack->top;
    while (count >= 0) {
        printf("%d\t", stack->data[count--]);
    }
    printf("\n");
    
}
