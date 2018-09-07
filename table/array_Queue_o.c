//
//  array_queue_o.c
//  data-structure
//
//  Created by determination on 2018/9/6.
//  Copyright © 2018年 determination. All rights reserved.
//

#include "array_queue_o.h"


bool isEmpty_AQ(ArrayQueue queue)
{
    return queue->size == 0;
}

bool isFull_AQ(ArrayQueue queue)
{
    return queue->size == queue->capacity;
}

void makeEmpty_AQ(ArrayQueue queue)
{
    queue->size = 0;
    queue->fornt = 1;
    queue->rear = 0;
}

void clear_AQ(ArrayQueue queue)
{
    makeEmpty_AQ(queue);
}

ArrayQueue newQueue_AQ(int maxSize)
{
    ArrayQueue queue = (ArrayQueue) malloc(sizeof(Queue_AQ));
    assert(queue != NULL);
    queue->data = (DataType *) malloc(sizeof(DataType) * maxSize);
    assert(queue != NULL);
    
    queue->capacity = maxSize;
    makeEmpty_AQ(queue);
    return queue;
}

static int succ(int value,ArrayQueue queue)
{
    if(++value == queue->capacity)
        value = 0;
    return value;
}

bool enqueue_AQ(ArrayQueue queue, DataType data)
{
    if (isFull_AQ(queue)) {
        printf("队列已满！");
        return false;
    }
    
    queue->size++;
    queue->rear = succ(queue->rear, queue);
    queue->data[queue->rear] = data;
    return true;
}

void disposeQueue_AQ(ArrayQueue queue)
{
    if (queue != NULL) {
        free(queue->data);
        free(queue);
    }
}

DataType front_AQ(ArrayQueue queue)
{
    if (isEmpty_AQ(queue)) {
        printf("队列为空");
        return -1;
    }
    return queue->data[queue->fornt];
}

bool dequeue_AQ(ArrayQueue queue)
{
    if (isEmpty_AQ(queue)) {
        printf("队列为空");
        return false;
    }
    
    queue->size--;
    queue->fornt = succ(queue->fornt, queue);
    return true;
}

DataType frontAndDequeue_AQ(ArrayQueue queue)
{
    if (isEmpty_AQ(queue)) {
        printf("队列为空");
        return false;
    }
    
    queue->size--;
    DataType tempCell = queue->data[queue->fornt];
    queue->fornt = succ(queue->fornt, queue);
    
    return tempCell;
}

int size_AQ(ArrayQueue queue)
{
    return queue->size;
}

int capacty_AQ(ArrayQueue queue)
{
    return queue->capacity;
}

void showQueue_AQ(ArrayQueue queue)
{
    if (isEmpty_AQ(queue)) {
        printf("\n");
        return;
    }
    
    if (queue->fornt < queue->rear) {
        for (int i = queue->fornt; i <= queue->rear; i++) {
            printf("%d\t", queue->data[i]);
        }
    } else {
        for (int i = queue->fornt; i < (queue->capacity - 1); i++) {
            printf("%d\t", queue->data[i]);
        }
        
        for (int i = 0; i <= queue->rear; i++) {
            printf("%d\t", queue->data[i]);
        }
    }
    
    
    printf("\n\n");
}
