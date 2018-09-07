//
//  linked_stack.c
//  data-structure
//
//  Created by determination on 2018/9/5.
//  Copyright © 2018年 determination. All rights reserved.
//

#include "linked_stack.h"
#define EMPTY_LS 0;

bool initLinedStack(LinkedStackPtr stack)
{
    stack->top = NULL;
    stack->size = EMPTY_LS;
    return true;
}

bool isEmpty_LS(LinkedStackPtr stack)
{
    return stack->size == EMPTY_LS;
}

bool push_LS(LinkedStackPtr stack, DataType data)
{
    StackNodePtr_LS node = (StackNodePtr_LS) malloc(sizeof(StackNode_LS));
    if (node == NULL) {
        printf("内存分配失败！");
        return false;
    }
    
    node->data = data;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
    return true;
}

void pop_LS(LinkedStackPtr stack)
{
    if (isEmpty_LS(stack)) {
        printf("栈内没有任何数据元素");
        return;
    }
    
    StackNodePtr_LS tempCell = stack->top;
    stack->top = tempCell->next;
    stack->size--;
    free(tempCell);
}

DataType topAndPop_LS(LinkedStackPtr stack)
{
    if (isEmpty_LS(stack)) {
        printf("栈内没有任何数据元素");
        return -1;
    }
    
    StackNodePtr_LS tempCell = stack->top;
    stack->top = tempCell->next;
    stack->size--;
    DataType data = tempCell->data;
    free(tempCell);
    return data;
}

int size_LS(LinkedStackPtr stack)
{
    return stack->size;
}

bool clear_LS(LinkedStackPtr stack)
{
    if (!isEmpty_LS(stack)) {
        
        while (stack->top) {
            StackNodePtr_LS tempCell = stack->top;
            stack->top = tempCell->next;
            free(tempCell);
        }
        stack->size = EMPTY_LS;
    }
    return true;
}

void showStack_LS(LinkedStackPtr stack)
{
    if (!isEmpty_LS(stack)) {
        StackNodePtr_LS tempCell = stack->top;
        while (tempCell) {
            printf("%d\t", tempCell->data);
            tempCell = tempCell->next;
        }
    }
    printf("\n");
}
