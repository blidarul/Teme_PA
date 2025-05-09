#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "queue.h"

#define JUCATORI 15

int main()
{
    srand((unsigned int)time(NULL));

    int hot_potato;
    hot_potato = rand() % JUCATORI;
    
    struct Queue jucatori;
    initQueue(&jucatori);
    
    int clasament[JUCATORI],k = 0;

    for(int i = 0; i < JUCATORI; i++)
    {
        enqueue(&jucatori,i + 1);
    }
    printf("Jucatori initiali:");
    printQueue(&jucatori);
//----------------------------------------------
    while(!QueueisEmpty(&jucatori))
    {
        if(jucatori.front > 0)
            moveQueueAT0(&jucatori);
        printf("HOT POTATO = %d\n",hot_potato);

        while(jucatori.front != hot_potato)
        {
            int valoare = jucatori.data[jucatori.front];
            dequeue(&jucatori);
            enqueue(&jucatori,valoare);
        }
        clasament[k++] = jucatori.data[jucatori.front];
        dequeue(&jucatori);

        if(!QueueisEmpty(&jucatori))
        {
            printf("Jucatori ramasi:");
            printQueue(&jucatori);
        }
        
        int size = jucatori.rear - jucatori.front;
        if(size)
            hot_potato = rand() % size;
    }
//----------------------------------------------
    printf("CLASAMENT\n");
    for(int i = 0; i < k; i++)
    {
        printf("%d ",clasament[i]);
    }
    printf("\n");
    return 0;
}