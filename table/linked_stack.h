//
//  linked_stack.h
//  data-structure
//
//  Created by determination on 2018/9/5.
//  Copyright © 2018年 determination. All rights reserved.
//

#ifndef linked_stack_h
#define linked_stack_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef void *DataType_LS;
typedef struct Node_LS {
    DataType_LS data;
    struct Node_LS *next;
} StackNode_LS, *StackNodePtr_LS;

typedef struct {
    int size;
    StackNodePtr_LS top;
} LinkedStack, *LinkedStackPtr;


LinkedStackPtr newLinkStack(void);

bool initLinedStack(LinkedStackPtr stack);

bool isEmpty_LS(LinkedStackPtr stack);

bool push_LS(LinkedStackPtr stack, DataType_LS data);

void pop_LS(LinkedStackPtr stack);

DataType_LS topAndPop_LS(LinkedStackPtr stack);

int size_LS(LinkedStackPtr stack);

bool clear_LS(LinkedStackPtr stack);

void showStack_LS(LinkedStackPtr stack);


#endif /* linked_stack_h */
