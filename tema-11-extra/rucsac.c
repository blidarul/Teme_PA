//Rezolvați problema rucsacului de la slide-ul 16.
//Este o problemă de optimizare care poate fi rezolvată atât recursiv 
//cât și prin programare dinamică. 
//Problemă:
//Capacitate maximă X
//Pot fi adăugate obiecte de greutate a,b,c cu diferite valori
//Se cere valoare maximă care poate fi atinsă

#include <stdio.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    #define n 10 // numarul greutatilor
    int w[n + 1] = {-1,  23,  26,  20,  18,  32,  27,  29,  26,  30,  27};
    int v[n + 1] = {-1, 505, 352, 458, 220, 354, 414, 498, 545, 473, 543};
    const int capacitate_rucsac = 67;
    int m[n + 1][capacitate_rucsac + 1];

    for(int i = 0; i <= capacitate_rucsac; i++)
    {
        m[0][i] = 0;
    }
    for(int i = 0; i <= n; i++)
    {
        m[i][0] = 0;
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= capacitate_rucsac; j++)
        {
            if(w[i] > j)
            {
                m[i][j] = m[i - 1][j];
            }
            else
            {
                m[i][j] = max(m[i - 1][j], m[i - 1][j - w[i]] + v[i]);
            }
        }
    }
    printf("%d\n", m[n][capacitate_rucsac]);

    return 0;
}