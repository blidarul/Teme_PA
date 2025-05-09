#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

void shuffle(int *v, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}


int Razboi(struct Queue *j1,struct Queue *j2)
{
    int round = 0;
    while(!QueueisEmpty(j1) && !QueueisEmpty(j2))
    {
        if(j1->data[j1->front] > j2->data[j2->front])
        {
            int aux = j1->data[j1->front];
            dequeue(j1);
            moveQueueAT0(j1);
            enqueue(j1,aux);
            enqueue(j1,j2->data[j2->front]);
            dequeue(j2);
        }
        else
        if(j1->data[j1->front] < j2->data[j2->front])
        {
            int aux = j2->data[j2->front];
            dequeue(j2);
            moveQueueAT0(j2);
            enqueue(j2,aux);
            enqueue(j2,j1->data[j1->front]);
            dequeue(j1);
        }
        else
        {
            dequeue(j1);
            dequeue(j2);
        }
        round ++;
    }
    return round;
}

int main()
{
    int pachet[52];
    
    struct Queue jucator1,jucator2;
    initQueue(&jucator1);
    initQueue(&jucator2);
    
    for(int i = 0; i < 52; i++)
    pachet[i] = i % 13 + 2;
    

    srand((unsigned int)time(NULL));
    shuffle(pachet,52);

    for(int i = 0; i < 52; i++)
        if(i < 26)
            enqueue(&jucator1,pachet[i]);
        else
            enqueue(&jucator2,pachet[i]);
    
    printf("Cartile jucatorului 1:\n\t");
    printQueue(&jucator1);
    printf("Cartile jucatorului 2:\n\t");
    printQueue(&jucator2);

    printf("Jocul a durat %d runde.\n",Razboi(&jucator1,&jucator2));
    if(!QueueisEmpty(&jucator1))
    {
        printf("Jucatorul 1 a castigat!\nCarti ramase:\n\t");
        printQueue(&jucator1);
    }
    else
    if(!QueueisEmpty(&jucator2))
    {
        printf("Jucatorul 2 a castigat!\nCarti ramase:\n\t");
        printQueue(&jucator2);
    }
    else
    {
        printf("Jocul este egal!\n");
    }

    return 0;
}