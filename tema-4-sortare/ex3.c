#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void INTswap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

int INTpartition(int v[],int L, int R)
{
    int pivot = v[R];
    int aux = L - 1;
    for(int i = L; i < R; i++)
    {
        if(v[i] < pivot)
        {
            aux ++;
            INTswap(&v[i],&v[aux]);
        }
    }
    INTswap(&v[R],&v[aux+1]);
    return aux + 1;
}

void INTQuickSort(int v[], int L, int R)
{
    int P;
    if(L < R)
    {
        P = INTpartition(v,L,R);
        INTQuickSort(v,L,P - 1);
        INTQuickSort(v,P + 1,R);
    }
    return;
}

int CautaSuma(int v[], int n, int suma, int *nr1, int *nr2)
{
    int stanga = 0,dreapta = n - 1;

    while(stanga < dreapta)
    {
        int s = v[stanga] + v[dreapta];
        if(s == suma)
        {
            *nr1 = v[stanga];
            *nr2 = v[dreapta];
            return 1;
        }
        if(s < suma)
            stanga ++;
        else
            dreapta --;
    }
    return 0;
}

int main()
{
    srand(time(NULL));
    const int N = 20;
    int numere[N];
    for(int i = 0; i < N; i++)
        numere[i] = rand() % (N*2);
    for(int i = 0; i < N; i++)
        printf("%d ",numere[i]);
    printf("\n");

    INTQuickSort(numere,0,N-1);

    while(1)
    {
        int suma,n1,n2;
        scanf("%d",&suma);
        if(suma == 0)
            break;
        if(CautaSuma(numere,N,suma,&n1,&n2))
        {
            printf("SUMA GASITA:\n%d + %d = %d\n",n1,n2,suma);
        }
        else
            printf("Suma nu a fost gasita\n");
    }
    

    return 0;
}