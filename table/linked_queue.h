//
//  linked_queue.h
//  data-structure
//
//  Created by determination on 2018/9/6.
//  Copyright © 2018年 determination. All rights reserved.
//

#ifndef linked_queue_h
#define linked_queue_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef int DataType_LQ;
typedef struct QueueNodeRecord {
    DataType_LQ data;
    struct QueueNodeRecord * next;
}QueueNode, * QueueNodePtr;

typedef struct {
    QueueNodePtr front;
    QueueNodePtr rear;
    int size;
} Queue_LQ, *LinkedQueue;

bool initLinkedQueue(LinkedQueue queue);
bool isEmpty_LQ(LinkedQueue queue);
bool enqueue_LQ(LinkedQueue queue, DataType_LQ data);
DataType_LQ front_LQ(LinkedQueue queue);
DataType_LQ frontAndDequeue_LQ(LinkedQueue queue);
bool dequeue_LQ(LinkedQueue queue);
void clear_LQ(LinkedQueue queue);
void dispose_LQ(LinkedQueue queue);
int size_LQ(LinkedQueue queue);
void showLinkedQueue_LQ(LinkedQueue queue);


#endif /* linked_queue_h */
