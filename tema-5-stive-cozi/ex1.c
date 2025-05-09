#include <stdio.h>
#include <stdbool.h>
#include "queue.h"
#include "stack.h"

int main()
{

    printf("QUEUE______________________________\n");
    struct Queue q;
    initQueue(&q);
    
    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    printQueue(&q);

    printf("Queue front element: %d\n", Queuepeek(&q));
    dequeue(&q);
    printf("Queue front element after dequeue: %d\n", Queuepeek(&q));
    clearQueue(&q);
    

    printf("STACK______________________________\n");
    struct Stack s;
    initStack(&s);

    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    printStack(&s);

    printf("Stack top element: %d\n", Stackpeek(&s));
    printf("Popped element: %d\n", pop(&s));
    printf("Stack top element after pop: %d\n", Stackpeek(&s));
    
    return 0;
}