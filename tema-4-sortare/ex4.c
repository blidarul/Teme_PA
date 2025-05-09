#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nume[20];
    float timp;
}ALERGATOR;

void FLOATInsertionSort(ALERGATOR v[], int n)
{
    for(int i = 0; i < n; i++)
    {
        ALERGATOR aux = v[i];
        int k;
        for(k = i - 1; k >= 0 && v[k].timp > aux.timp; k--)
            v[k + 1] = v[k];
        v[k + 1] = aux;
    }
    return;
}

void AfisareClasament(ALERGATOR v[],int n)
{
    FLOATInsertionSort(v,n);
    int i;
    for(i = 0; i < n; i++)
        printf("%d.%s\n",i+1,v[i].nume);
    return;
}

int main()
{
    const int N = 10;
    ALERGATOR v[10] = { {"Mihai",8.77},
                        {"Ana", 8.75},
                        {"George",10.22},
                        {"Andrei",9.85},
                        {"Ioana",10.85},
                        {"Cristina",9.93},
                        {"Alex",9.99},
                        {"Vlad",10},
                        {"Matei",11.45},
                        {"Dani",10.15}};

    AfisareClasament(v,N);

    return 0;
}