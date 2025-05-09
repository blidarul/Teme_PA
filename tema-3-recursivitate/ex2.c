#include <stdio.h>
#include <stdlib.h>

int const DISK = 6;
int sursa[6] = {1,2,3,4,5,6}, destinatie[8] = {0,0,0,0,0,0}, auxiliar[8] = {0,0,0,0,0,0};

void afisareTurnuri()
{
    for(int k = 0; k < DISK; k++)
    {
        if(sursa[k] == 0)
            printf(" - ");
        else
            printf(" %d ",sursa[k]);
        
        if(destinatie[k] == 0)
            printf(" - ");
        else
            printf(" %d ",destinatie[k]);
        
        if(auxiliar[k] == 0)
            printf(" - ");
        else
            printf(" %d ",auxiliar[k]);
        printf("\n");
    }
}

void muta(int disk,int source[],int dest[])
{
    int i = 0;
    int j = 0;
    while(source[i] == 0)
        i++;
    while(dest[j + 1] == 0 && j < DISK - 1)
        j++;
    if(source[i] == disk)
    {       
        dest[j] = source[i];
        source[i] = 0;
    }
    else
    {
        printf("eroare");
        exit(1);
    }
}

void Hanoi(int disk, int source[], int dest[], int aux[])
{
    if(disk == 1)
    {
        muta(disk,source,dest);
        afisareTurnuri(disk);
        printf("=============\n");
    }
    else
    {
        Hanoi(disk - 1,source,aux,dest);
        muta(disk,source,dest);
        afisareTurnuri(disk);
        printf("=============\n");
        Hanoi(disk - 1,aux,dest,source);
    }
}

int main()
{
    afisareTurnuri();
    printf("=============\n");
    Hanoi(DISK,sursa,destinatie,auxiliar);

    return 0;
}