#include <stdio.h>

void afisare(int v[],int n,int i)
{
    if(i < n)
    {
        printf("%d ",v[i]);
        afisare(v,n,i+1);
    }
}

int main()
{
    int n = 20,v[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

    afisare(v,n,0);

    return 0;
}