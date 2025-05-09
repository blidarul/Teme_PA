#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

struct QueueUsingStacks
{
    struct Stack stack1;
    struct Stack stack2;
};

void initQueueUsingStacks(struct QueueUsingStacks* q)
{
    initStack(&q->stack1);
    initStack(&q->stack2);
}

void transferElements(struct Stack* source, struct Stack* destination)
{
    while (!StackisEmpty(source)) {
        push(destination, pop(source));
    }
}

bool enqueueUsingStacks(struct QueueUsingStacks* q, int value)
{

    transferElements(&q->stack1, &q->stack2);
    push(&q->stack1, value);
    transferElements(&q->stack2, &q->stack1);
    return true;
}

int dequeueUsingStacks(struct QueueUsingStacks* q)
{
    return pop(&q->stack1);
}

void printQueueUsingStacks(struct QueueUsingStacks* q)
{
    printf("Queue elements (rear to front): ");
    
    struct Stack tempStack;
    initStack(&tempStack);
    
    struct Stack stack2Copy = q->stack2;
    while (!StackisEmpty(&stack2Copy))
    {
        push(&tempStack, pop(&stack2Copy));
    }
    while (!StackisEmpty(&tempStack))
    {
        printf("%d ", pop(&tempStack));
    }
    
    struct Stack stack1Copy = q->stack1;
    while (!StackisEmpty(&stack1Copy))
    {
        push(&tempStack, pop(&stack1Copy));
    }
    while (!StackisEmpty(&tempStack))
    {
        printf("%d ", pop(&tempStack));
    }
    printf("\n");
}

int main()
{
    struct QueueUsingStacks q;
    initQueueUsingStacks(&q);
    
    printf("Enqueuing elements: 1, 2, 3, 4, 5, 6\n");
    enqueueUsingStacks(&q, 1);
    enqueueUsingStacks(&q, 2);
    enqueueUsingStacks(&q, 3);
    enqueueUsingStacks(&q, 4);
    enqueueUsingStacks(&q, 5);
    enqueueUsingStacks(&q, 6);
    
    printQueueUsingStacks(&q);
    
    printf("\nDequeuing two elements:\n");
    printf("Dequeued: %d\n", dequeueUsingStacks(&q));
    printf("Dequeued: %d\n", dequeueUsingStacks(&q));
    
    printf("\nQueue after dequeuing:\n");
    printQueueUsingStacks(&q);
    
    printf("\nEnqueuing elements: 7, 8\n");
    enqueueUsingStacks(&q, 7);
    enqueueUsingStacks(&q, 8);

    printf("\nDequeuing two elements:\n");
    printf("Dequeued: %d\n", dequeueUsingStacks(&q));
    printf("Dequeued: %d\n", dequeueUsingStacks(&q));

    printf("\nEnqueuing elements: 9, 10\n");
    enqueueUsingStacks(&q, 9);
    enqueueUsingStacks(&q, 10);
    
    printf("Final queue state:\n");
    printQueueUsingStacks(&q);
    
    return 0;
}