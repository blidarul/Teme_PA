#include <stdio.h>

int fib(int nr)
{
    if(nr<= 1)
        return nr;
    else
    {
        int aux = fib(nr - 1) + fib(nr - 2);
        return aux;
    }
}

int main()
{
    int n = 30;
    int x = 0,y = 1;
    int i = 0;
    
    printf("---------ITERATIV-----------");
    printf("\nSirul lui fibonacci pana la numarul %d din  este:\n",n);
    while(i < n)
    {
        printf("%d ",x);
        int aux = y;
        y = x + y;
        x = aux;
        i++;
    }
    printf("%d ",x);
    printf("\n---------RECURSIV-----------");
    printf("\nSirul lui fibonacci pana la numarul %d din  este:\n",n);
    for(i = 0; i <= 30; i++)
        printf("%d ",fib(i));
    
    return 0;
}