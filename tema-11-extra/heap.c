#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

Heap* createHeap(unsigned int capacity)
{
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (int*)malloc(sizeof(int) * capacity);
    return heap;
}

int peek(Heap *heap)
{
    if(heap->size == 0)
    {
        printf("Heap gol\n");
        return -1;
    }
    return heap->array[0];
}

static void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void heapifyMin(Heap *heap, unsigned int index)
{
    unsigned int left = 2 * index + 1;
    unsigned int right = 2 * index + 2;
    unsigned int smallest = index;

    if(left < heap->size && heap->array[left] < heap->array[smallest])
    {
        smallest = left;
    }

    if(right < heap->size && heap->array[right] < heap->array[smallest])
    {
        smallest = right;
    }

    if(smallest != index)
    {
        swap(&heap->array[smallest], &heap->array[index]);
        heapifyMin(heap, smallest);
    }

}

static void heapifyMax(Heap *heap, unsigned int index)
{
    unsigned int left = 2 * index + 1;
    unsigned int right = 2 * index + 2;
    unsigned int biggest = index;

    if(right < heap->size && heap->array[right] > heap->array[biggest])
    {
        biggest = right;
    }

    if(left < heap->size && heap->array[left] > heap->array[biggest])
    {
        biggest = left;
    }

    if(biggest != index)
    {
        swap(&heap->array[biggest], &heap->array[index]);
        heapifyMax(heap, biggest);
    }
}

int extractMin(Heap *heap)
{
    if(heap->size == 0)
    {
        printf("Heap gol\n");
        return -1;
    }

    int root = heap->array[0];

    heap->array[0] = heap->array[heap->size - 1];
    heap->size --;

    heapifyMin(heap, 0);

    return root;
}

int extractMax(Heap *heap)
{
    if(heap->size == 0)
    {
        printf("Heap gol");
        return -1;
    }

    int root = heap->array[0];

    heap->array[0] = heap->array[heap->size - 1];
    heap->size --;

    heapifyMax(heap, 0);

    return root;
}

void insertMin(Heap *heap, int value)
{
    if(heap->size == heap->capacity)
    {
        printf("Heap plin\n");
        return;
    }

    heap->size ++;
    
    unsigned int i = heap->size - 1;

    heap->array[i] = value;

    while(i != 0 && heap->array[i] < heap->array[(i - 1) / 2])
    {
        swap(&heap->array[(i - 1) / 2], &heap->array[i]);
        i = (i - 1) / 2;
    }
}

void insertMax(Heap *heap, int value)
{
    if(heap->size == heap->capacity)
    {
        printf("Heap plin\n");
        return;
    }

    heap->size ++;
    
    unsigned int i = heap->size - 1;

    heap->array[i] = value;

    while(i != 0 && heap->array[i] > heap->array[(i - 1) / 2])
    {
        swap(&heap->array[(i - 1) / 2], &heap->array[i]);
        i = (i - 1) / 2;
    }
}

void heapSort(int array[], unsigned int n, ORDER order)
{
    Heap *heap = createHeap(n);

    for(unsigned int i = 0; i < n; i++)
    {
        if(order == ASCENDING)
        {
            insertMax(heap, array[i]);
        }
        else
        if(order == DESCENDING)
        {
            insertMin(heap, array[i]);
        }
    }

    for(int i = (int)n - 1; i >= 0; i--)
    {
        if(order == ASCENDING)
        {
            array[i] = extractMax(heap);
        }
        else
        if(order == DESCENDING)
        {
            array[i] = extractMin(heap);
        }
    }

    freeHeap(heap);
}

void freeHeap(Heap *heap)
{
    free(heap->array);
    free(heap);
}