//
//  array_queue_o.h
//  data-structure
//
//  Created by determination on 2018/9/6.
//  Copyright © 2018年 determination. All rights reserved.
//

#ifndef array_queue_o_h
#define array_queue_o_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef int DataType_AQ;
typedef struct QueueRecord {
    int capacity;
    int front;
    int rear;
    int size;
    DataType_AQ* data;
} Queue_AQ, *ArrayQueue;

bool isEmpty_AQ(ArrayQueue queue);
bool isFull_AQ(ArrayQueue queue);
ArrayQueue newQueue_AQ(int maxSize);
void disposeQueue_AQ(ArrayQueue queue);
void makeEmpty_AQ(ArrayQueue queue);
void clear_AQ(ArrayQueue queue);
bool enqueue_AQ(ArrayQueue queue, DataType_AQ data);
DataType_AQ front_AQ(ArrayQueue queue);
bool dequeue_AQ(ArrayQueue queue);
DataType_AQ frontAndDequeue_AQ(ArrayQueue queue);
int size_AQ(ArrayQueue queue);
int capacty_AQ(ArrayQueue queue);
void showQueue_AQ(ArrayQueue queue);

#endif /* array_queue_o_h */
