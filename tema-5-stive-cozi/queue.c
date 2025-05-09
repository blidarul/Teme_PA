#include <stdio.h>
#include "queue.h"

void initQueue(struct Queue* q)
{
    q->front = 0;
    q->rear = 0;
}

bool QueueisEmpty(struct Queue* q)
{
    return q->front == q->rear;
}

bool moveQueueAT0(struct Queue *q)
{
    if(q->front > 0)
    {
        int decalare = q->front;
        int size = q->rear - q->front;
        for(int i = 0; i < size; i++)
        {
            q->data[i] = q->data[i + decalare];
        }
        q->front = 0;
        q->rear = size;
        return true;
    }
    else
    {
        printf("Queue already at start!\n");
        return false;
    }
}

bool enqueue(struct Queue* q, int value)
{
    if (q->rear < QUEUE_MAX_SIZE)
    {
        q->data[q->rear++] = value;
        return true;
    }
    else
    {
        printf("Queue is full\n");
        return false;
    }
}

bool dequeue(struct Queue* q) 
{
    if (!QueueisEmpty(q))
    {
        q->front++;
        return true;
    }
    else
    {
        printf("Queue is empty\n");
        return false;
    }
}

int Queuepeek(struct Queue* q) 
{
    if (q->front < q->rear) 
        return q->data[q->front];
    else 
        printf("Queue is empty\n");
    return -1;
}

void clearQueue(struct Queue* q)
{
    q->front = 0;
    q->rear = 0;
}

bool printQueue(struct Queue *q)
{
    if(!QueueisEmpty(q))
    {
        for (int i = q->front; i < q->rear; i++)
        {
            printf("%d ", q->data[i]);
        }
        printf("\n");
        return true;
    }
    else
    {
        printf("Queue is empty!\n");
        return false;
    }
}
