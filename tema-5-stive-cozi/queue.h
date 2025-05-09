#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#define QUEUE_MAX_SIZE 100

struct Queue
{
    int data[QUEUE_MAX_SIZE];
    int front;
    int rear;
};

void initQueue(struct Queue* q);
bool QueueisEmpty(struct Queue* q);
bool enqueue(struct Queue* q, int value);
bool dequeue(struct Queue* q);
int Queuepeek(struct Queue* q);
void clearQueue(struct Queue* q);
bool printQueue(struct Queue *q);
bool moveQueueAT0(struct Queue *q);

#endif