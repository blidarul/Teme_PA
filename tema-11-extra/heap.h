#ifndef HEAP_H
#define HEAP_H

typedef struct Heap
{
    int *array;
    unsigned int size;
    unsigned int capacity;
} Heap;

typedef enum
{
    NONE = 0,
    ASCENDING,
    DESCENDING
} ORDER;

Heap* createHeap(unsigned int capacity);

int peek(Heap *heap);

int extractMin(Heap *heap);

int extractMax(Heap *heap);

void insertMin(Heap *heap, int value);

void insertMax(Heap *heap, int value);

void heapSort(int array[], unsigned int n, ORDER order);

void freeHeap(Heap *heap);

#endif