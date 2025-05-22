#include "heap.h"
#include <stdio.h>

int main()
{
    int array[] = {6, 18, 87, 1, 35, -7, 6, 43, 39, 69, 420};
    unsigned int n = sizeof(array) / sizeof(int);

    printf("Vector sortat crescator: ");
    heapSort(array, n, ASCENDING);
    for(unsigned int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("Vector sortat descrescator: ");
    heapSort(array, n, DESCENDING);
    for(unsigned int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
    return 0;
}