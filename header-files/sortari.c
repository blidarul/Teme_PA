void INTswap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void CHARswap(char *a, char *b)
{
    char aux = *a;
    *a = *b;
    *b = aux;
    return;
}

void FLOATswap(float *a, float *b)
{
    float aux = *a;
    *a = *b;
    *b = aux;
    return;
}

void CHARBubbleSort(char v[], int n)
{
    for(int i = 0; i < n; i++)
    for(int j = 0; j < n - 1; j++)
        if(v[j] > v[j + 1])
            CHARswap(&v[j],&v[j+1]);
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

void FLOATBubbleSort(float v[], int n)
{
    for(int i = 0; i < n; i++)
    for(int j = 0; j < n - 1; j++)
        if(v[j] > v[j + 1])
            FLOATswap(&v[j],&v[j+1]);
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

void CHARInsertionSort(char v[], int n)
{
    for(int i = 0; i < n; i++)
    {
        char aux = v[i];
        int k;
        for(k = i - 1; k >= 0 && v[k] > aux; k--)
            v[k + 1] = v[k];
        v[k + 1] = aux;
    }
    return;
}

void FLOATInsertionSort(float v[], int n)
{
    for(int i = 0; i < n; i++)
    {
        float aux = v[i];
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

void CHARSelectionSort(char v[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        char min = v[i];
        int poz = i;
        for(int j = i; j < n; j++)
            if(v[j] < min)
            {
                min = v[j];
                poz = j;
            }
        CHARswap(&v[i],&v[poz]);
    }
    return;
}

void FLOATSelectionSort(float v[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        float min = v[i];
        int poz = i;
        for(int j = i; j < n; j++)
            if(v[j] < min)
            {
                min = v[j];
                poz = j;
            }
        FLOATswap(&v[i],&v[poz]);
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

void CHARmerge(char *l1, char *l2,int n,char *l3)
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

void CHARMergeSort(char *l, int n)
{
    if(n == 1)
        return;
    char l1[n/2],l2[n - n/2];
    for(int i = 0; i <= n/2; i ++)
    {
        l1[i] = l[i];
        l2[i] = l[n/2 + i];
    }
    CHARMergeSort(l1,n/2);
    CHARMergeSort(l2,n - n/2);
    CHARmerge(l1,l2,n,l);
    return;
}

void FLOATmerge(float *l1, float *l2,int n,float *l3)
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

void FLOATMergeSort(float *l, int n)
{
    if(n == 1)
        return;
    float l1[n/2],l2[n - n/2];
    for(int i = 0; i <= n/2; i ++)
    {
        l1[i] = l[i];
        l2[i] = l[n/2 + i];
    }
    FLOATMergeSort(l1,n/2);
    FLOATMergeSort(l2,n - n/2);
    FLOATmerge(l1,l2,n,l);
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

int CHARpartition(char v[],int L, int R)
{
    char pivot = v[R];
    int aux = L - 1;
    for(int i = L; i < R; i++)
    {
        if(v[i] < pivot)
        {
            aux ++;
            CHARswap(&v[i],&v[aux]);
        }
    }
    CHARswap(&v[R],&v[aux+1]);
    return aux + 1;
}

void CHARQuickSort(char v[], int L, int R)
{
    int P;
    if(L < R)
    {
        P = CHARpartition(v,L,R);
        CHARQuickSort(v,L,P - 1);
        CHARQuickSort(v,P + 1,R);
    }
    return;
}

int FLOATpartition(float v[],int L, int R)
{
    float pivot = v[R];
    int aux = L - 1;
    for(int i = L; i < R; i++)
    {
        if(v[i] < pivot)
        {
            aux ++;
            FLOATswap(&v[i],&v[aux]);
        }
    }
    FLOATswap(&v[R],&v[aux+1]);
    return aux + 1;
}

void FLOATQuickSort(float v[], int L, int R)
{
    int P;
    if(L < R)
    {
        P = FLOATpartition(v,L,R);
        FLOATQuickSort(v,L,P - 1);
        FLOATQuickSort(v,P + 1,R);
    }
    return;
}