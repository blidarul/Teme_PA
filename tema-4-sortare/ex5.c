#include <stdio.h>

void INTafisare(int *v, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ",*(v + i));
    printf("\n");
    return;
}

int Max(int v[], int n)
{
    int max = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] > max)
            max = v[i];
    return max;
}

void countSort(int v[], int n, int ordin)
{
    int output[n];
    //creare vector de aparitii
    int count[10] = {0};

    // numarare aparitii ale cifrei in functie de ordin
    for (int i = 0; i < n; i++)
        count[(v[i] / ordin) % 10]++;

    // scchimba count[i] sa contina cifra ce trebuie in output
    for (int i = 1; i < 10; i++)
        count[i] = count[i] + count[i - 1];

    //construieste output
    for (int i = n - 1; i >= 0; i--)
    {
        int cifra = (v[i] / ordin) % 10;
        output[count[cifra] - 1] = v[i];
        count[cifra]--;
    }

    //copiaza output in v astfel incat v este sortat dupa cifra unitaltilor/zeccilor/sutelor(dupa ordin)
    for (int i = 0; i < n; i++)
        v[i] = output[i];
}

void radixSort(int v[], int n)
{
    //aflam maximul pentru a sti cate cifre are cel mai mare numar
    int max = Max(v, n);

    for (int ordin = 1; max / ordin > 0; ordin *= 10)
        countSort(v, n, ordin);
}

int main()
{
    int v[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(v) / sizeof(v[0]);

    radixSort(v, n);
    INTafisare(v, n);
    return 0;
}

//algoritmul sorteaza vectorul de mai multe ori;
// prima data in functie de cifra unitatilor, (count sort)
// apoi dupa cifra zecilor, (count sort)
// si tot asa pana vectorul este sortat (count sort)
// radix sort de fapt foloseste un count sort rudimentar de mai multe ori(cate cifre are cel mai mare numar) pentru a sorta vectorul