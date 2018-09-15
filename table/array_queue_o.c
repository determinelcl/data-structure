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
    queue->front = 1;
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
    queue->data = (DataType_AQ *) malloc(sizeof(DataType_AQ) * maxSize);
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

bool enqueue_AQ(ArrayQueue queue, DataType_AQ data)
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

DataType_AQ front_AQ(ArrayQueue queue)
{
    if (isEmpty_AQ(queue)) {
        printf("队列为空");
        return -1;
    }
    return queue->data[queue->front];
}

bool dequeue_AQ(ArrayQueue queue)
{
    if (isEmpty_AQ(queue)) {
        printf("队列为空");
        return false;
    }
    
    queue->size--;
    queue->front = succ(queue->front, queue);
    return true;
}

DataType_AQ frontAndDequeue_AQ(ArrayQueue queue)
{
    if (isEmpty_AQ(queue)) {
        printf("队列为空");
        return false;
    }
    
    queue->size--;
    DataType_AQ tempCell = queue->data[queue->front];
    queue->front = succ(queue->front, queue);
    
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
    
    if (queue->front < queue->rear) {
        for (int i = queue->front; i <= queue->rear; i++) {
            printf("%d\t", queue->data[i]);
        }
    } else {
        for (int i = queue->front; i < (queue->capacity - 1); i++) {
            printf("%d\t", queue->data[i]);
        }
        
        for (int i = 0; i <= queue->rear; i++) {
            printf("%d\t", queue->data[i]);
        }
    }
    
    
    printf("\n\n");
}
