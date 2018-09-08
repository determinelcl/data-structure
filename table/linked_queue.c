//
//  linked_queue.c
//  data-structure
//
//  Created by determination on 2018/9/6.
//  Copyright © 2018年 determination. All rights reserved.
//

#include "linked_queue.h"
#define EMPTY_LQ 0

bool initLinkedQueue(LinkedQueue queue)
{
    assert(queue != NULL);
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = EMPTY_LQ;
    return true;
}


bool isEmpty_LQ(LinkedQueue queue)
{
    return queue->size == EMPTY_LQ;
}

bool enqueue_LQ(LinkedQueue queue, DataType_LQ data)
{
    assert(queue != NULL);
    QueueNodePtr tempCell = (QueueNodePtr) malloc(sizeof(QueueNode));
    assert(tempCell != NULL);
    
    tempCell->data = data;
    tempCell->next = NULL;
    if (isEmpty_LQ(queue)) {
        queue->front = queue->rear = tempCell;
    } else {
        queue->rear->next = tempCell;
        queue->rear = tempCell;
    }
    
    queue->size++;
    return true;
}

DataType_LQ front_LQ(LinkedQueue queue)
{
    assert(queue != NULL);
    if (isEmpty_LQ(queue)) {
        printf("队列为空");
        return  NULL;
    }
    
    return queue->front->data;
}

DataType_LQ frontAndDequeue_LQ(LinkedQueue queue)
{
    assert(queue);
    
    if (isEmpty_LQ(queue)) {
        printf("队列为空");
        return NULL;
    }
    
    QueueNodePtr temp = queue->front;
    queue->front = temp->next;
    DataType_LQ data = temp->data;
    queue->size--;
    free(temp);
    return data;
}

bool dequeue_LQ(LinkedQueue queue)
{
    assert(queue);
    
    if (isEmpty_LQ(queue)) {
        printf("队列为空");
        return false;
    }
    
    QueueNodePtr temp = queue->front;
    queue->front = temp->next;
    queue->size--;
    free(temp);
    
    return true;
}

void clear_LQ(LinkedQueue queue)
{
    if (queue == NULL)
        return;
    
    if (!isEmpty_LQ(queue)) {
        QueueNodePtr temp = queue->front;
        while (temp) {
            QueueNodePtr cell = temp;
            temp = temp->next;
            free(cell);
        }
    }
    
    queue->front = queue->rear = NULL;
    queue->size = EMPTY_LQ;
}

void dispose_LQ(LinkedQueue queue)
{
    if (queue == NULL)
        return;

    clear_LQ(queue);
    free(queue);
}

int size_LQ(LinkedQueue queue)
{
    return queue->size;
}

void showLinkedQueue_LQ(LinkedQueue queue)
{
    assert(queue != NULL);
    
    if (!isEmpty_LQ(queue)) {
        QueueNodePtr temp = queue->front;
        while (temp) {
            printf("%d\t", *(int *)temp->data);
            temp = temp->next;
        }
    }
    printf("\n\n");
}
