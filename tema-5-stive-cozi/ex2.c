#include <stdio.h>
#include <stdbool.h>
#define STACK_MAX_SIZE 100

struct DoubleStack
{
    int data[STACK_MAX_SIZE];
    int top1; 
    int top2;
};

void initDoubleStack(struct DoubleStack* ds)
{
    ds->top1 = -1;
    ds->top2 = STACK_MAX_SIZE;
}

bool push1(struct DoubleStack* ds, int value)
{
    if (ds->top1 < ds->top2 - 1)
    {
        ds->data[++ds->top1] = value;
        return true;
    }
    printf("Stack 1 is full\n");
    return false;
}

bool push2(struct DoubleStack* ds, int value)
{
    if (ds->top1 < ds->top2 - 1)
    {
        ds->data[--ds->top2] = value;
        return true;
    }
    printf("Stack 2 is full\n");
    return false;
}

int pop1(struct DoubleStack* ds)
{
    if (ds->top1 >= 0)
    {
        return ds->data[ds->top1--];
    }
    printf("Stack 1 is empty\n");
    return -1;
}

int pop2(struct DoubleStack* ds)
{
    if (ds->top2 < STACK_MAX_SIZE)
    {
        return ds->data[ds->top2++];
    }
    printf("Stack 2 is empty\n");
    return -1;
}

void printStacks(struct DoubleStack* ds)
{
    printf("Stack 1: ");
    for (int i = 0; i <= ds->top1; i++)
        printf("%d ", ds->data[i]);
    printf("\nStack 2: ");
    for (int i = STACK_MAX_SIZE - 1; i >= ds->top2; i--)
        printf("%d ", ds->data[i]);
    
    printf("\n");
}

int main()
{
    struct DoubleStack ds;
    initDoubleStack(&ds);

    printf("Pushing elements to Stack 1:\n");
    push1(&ds, 1);
    push1(&ds, 2);
    push1(&ds, 3);

    
    printf("Pushing elements to Stack 2:\n");
    push2(&ds, 10);
    push2(&ds, 20);
    push2(&ds, 30);

    printStacks(&ds);

    
    printf("\nPopping from Stack 1: %d\n", pop1(&ds));
    printf("Popping from Stack 2: %d\n", pop2(&ds));

    
    printf("\nFinal state of stacks:\n");
    printStacks(&ds);

    return 0;
}