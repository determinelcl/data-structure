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

typedef int DataType;
typedef struct Node_LS
{
    DataType data;
    struct Node_LS * next;
} StackNode_LS, *StackNodePtr_LS ;

typedef struct
{
    int size;
    StackNodePtr_LS top;
} LinkedStack, *LinkedStackPtr;

bool initLinedStack(LinkedStackPtr stack);
bool isEmpty_LS(LinkedStackPtr stack);
bool push_LS(LinkedStackPtr stack, DataType data);
void pop_LS(LinkedStackPtr stack);
DataType topAndPop_LS(LinkedStackPtr stack);
int size_LS(LinkedStackPtr stack);
bool clear_LS(LinkedStackPtr stack);
void showStack_LS(LinkedStackPtr stack);


#endif /* linked_stack_h */
