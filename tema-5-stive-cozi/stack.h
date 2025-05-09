#ifndef STACK_H
#define STACK_H
#define STACK_MAX_SIZE 100

#include <stdbool.h>

struct Stack 
{
    int data[STACK_MAX_SIZE];
    int top;
};

void initStack(struct Stack* s);
bool StackisEmpty(struct Stack* s);
int pop(struct Stack* s);
bool push(struct Stack* s, int value);
int Stackpeek(struct Stack* s);
void clearStack(struct Stack* s);
void printStack(struct Stack* s);


#endif