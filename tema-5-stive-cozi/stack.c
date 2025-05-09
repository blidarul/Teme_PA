#include "stack.h"
#include <stdio.h>

void initStack(struct Stack* s)
{
    s->top = -1;
}

bool StackisEmpty(struct Stack* s)
{
    return s->top == -1;
}

int pop(struct Stack* s)
{
    if (!StackisEmpty(s)) 
        return s->data[s->top--];
    else
        printf("Stack is empty\n");
    return -1;
}

bool push(struct Stack* s, int value)
{
    if (s->top < STACK_MAX_SIZE - 1)
    {
        s->data[++s->top] = value;
        return true;
    }
    else
    {
        printf("Stack is full\n");
        return false;
    }
}

int Stackpeek(struct Stack* s)
{
    if (!StackisEmpty(s)) 
        return s->data[s->top];
    else
        printf("Stack is empty\n");
    return -1;
}

void clearStack(struct Stack* s)
{
    s->top = -1;
}

void printStack(struct Stack* s)
{
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}