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

void INTBubbleSort(int v[], int n)
{
    int ok = 1;
    for(int i = 0; i < n && ok == 1; i++)
    {
        ok = 0;
        for(int j = 0; j < n - 1; j++)
            if(v[j] > v[j + 1])
            {
                INTswap(&v[j],&v[j+1]);
                ok = 1;
            }
    }   
    return;
}

void INTInsertionSort(int v[], int n)
{
    for(int i = 0; i < n; i++)
    {
        int aux = v[i];
        int k;
        for(k = i - 1; k >= 0 && v[k] > aux; k--)
            v[k + 1] = v[k];
        v[k + 1] = aux;
    }
    return;
}

void INTSelectionSort(int v[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int min = v[i];
        int poz = i;
        for(int j = i; j < n; j++)
            if(v[j] < min)
            {
                min = v[j];
                poz = j;
            }
        INTswap(&v[i],&v[poz]);
    }
    return;
}

void INTmerge(int *l1, int *l2,int n,int *l3)
{
    int k = 0;
    int i = 0,n1 = n/2;
    int j = 0,n2 = n - n/2;
    while(i < n1 && j < n2)
    {
        if(l1[i] > l2[j])
        {
            l3[k] = l2[j];
            j ++;
            k ++;
        }
        else
        {
            l3[k] = l1[i];
            i ++;
            k ++;
        }
    }

    while(i < n1)
    {
        l3[k] = l1[i];
        i ++;
        k ++;
    }

    while(j < n2)
    {
        l3[k] = l2[j];
        j ++;
        k ++;
    }
    return;
}

void INTMergeSort(int *l, int n)
{
    if(n == 1)
        return;
    int l1[n/2],l2[n - n/2];
    
    for(int i = 0; i <= n/2; i ++)
    {
        l1[i] = l[i];
        l2[i] = l[n/2 + i];
    }
    INTMergeSort(l1,n/2);
    INTMergeSort(l2,n - n/2);
    INTmerge(l1,l2,n,l);
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

int main()
{
    srand(time(NULL));
    const int N = 100000;
    int random[N],i;
    clock_t timp,t[5];

    for(i = 0; i < N; i++)
        random[i] = rand() % N;
    
    printf("TIMPI RULARE PENTRU %d NUMERE\n",N);
    //Bubble sort
    printf("\n1.Bubble:");

    timp = clock();
    INTBubbleSort(random,N);
    timp = clock() - timp;
    t[0] = timp;

    printf("\nClock ticks: %d (%f secunde).\n", timp, ((float)timp) / CLOCKS_PER_SEC);
    
    for(i = 0; i < N; i++)
        random[i] = rand() % N;

    //Insertion sort
    printf("\n2.Insertion:");

    timp = clock();
    INTInsertionSort(random,N);
    timp = clock() - timp;
    t[1] = timp;

    printf("\nClock ticks: %d (%f secunde).\n", timp, ((float)timp) / CLOCKS_PER_SEC);

    for(i = 0; i < N; i++)
        random[i] = rand() % N;
    
    //Selection sort
    printf("\n3.Selection:");

    timp = clock();
    INTSelectionSort(random,N);
    timp = clock() - timp;
    t[2] = timp;

    printf("\nClock ticks: %d (%f secunde).\n", timp, ((float)timp) / CLOCKS_PER_SEC);

    for(i = 0; i < N; i++)
        random[i] = rand() % N;

    //Merge sort
    printf("\n4.Merge:");

    timp = clock();
    INTMergeSort(random,N);
    timp = clock() - timp;
    t[3] = timp;

    printf("\nClock ticks: %d (%f secunde).\n", timp, ((float)timp) / CLOCKS_PER_SEC);
    
    for(i = 0; i < N; i++)
        random[i] = rand() % N;

    //Quick sort
    printf("\n5.Quick:");

    timp = clock();
    INTQuickSort(random,0,N - 1);
    timp = clock() - timp;
    t[4] = timp;

    printf("\nClock ticks: %d (%f secunde).\n", timp, ((float)timp) / CLOCKS_PER_SEC);

    int min = t[0],minP = 0;
    for(int j = 1; j < 5; j++)
    {
        if(t[j] < min)
        {
            min = t[j];
            minP = j;
        }
    }

    printf("\nCel mai rapid algoritm a fost algoritmul %d.",minP + 1);
    return 0;
}