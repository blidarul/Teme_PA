#include <stdio.h>

int unassigned(int sudoku[][9],int x, int y)
{
    if(sudoku[x][y] == 0)
        return 1;
    else 
        return 0;
}

int verLinie(int sudoku[][9],int x,int valoare)
{
    for(int i = 0;i < 9; i++)
    {
        if(sudoku[x][i] == valoare)
            return 0;
    }
    return 1;
}

int verColoana(int sudoku[][9],int y,int valoare)
{
    for(int i = 0;i < 9; i++)
    {
        if(sudoku[i][y] == valoare)
            return 0;
    }
    return 1;
}

int verPatrat(int sudoku[][9],int x, int y, int valoare)
{
    int x_s = (x/3) * 3;
    int x_d = (x/3 + 1) * 3;
    int y_s = (y/3) * 3;
    int y_j = (y/3 + 1) * 3;
    for(int i = x_s; i < x_d; i++)
    for(int j = y_s; j < y_j; j++)
        if(sudoku[i][j] == valoare)
            return 0;
    return 1;
}

int is_safe(int sudoku[][9],int x,int y,int valoare)
{ 
    return ((verLinie(sudoku,x,valoare) && verColoana(sudoku,y,valoare)) && verPatrat(sudoku,x,y,valoare)) && unassigned(sudoku,x,y);
}

void afisare(int sudoku[][9])
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            printf("%d ",sudoku[i][j]);
            if(j % 3 == 2 && j < 8)
                printf("|");
            else
                printf(" ");
        }
        if(i % 3 == 2 && i < 8)
            printf("\n_________________________\n");
        else 
            printf("\n");
    }
    return;
}

int solve(int sudoku[][9],int x, int y)
{
    if(x == 8 && y == 9)
        return 1;
    if(y == 9)
    {
        x ++;
        y = 0;
    }
    if(!unassigned(sudoku,x,y))
        return solve(sudoku,x,y+1);
    
    for(int val = 1; val <= 9; val++)
    {
        if(is_safe(sudoku,x,y,val))
        {
            sudoku[x][y] = val;
            if(solve(sudoku,x,y+1))
                return 1;
            sudoku[x][y] = 0;
        }
    }
    return 0;
}

int main()
{
    int sudoku[9][9] = 
    {
        {0,0,0,0,0,0,0,0,8},
        {1,8,0,0,0,2,3,0,0},
        {0,6,0,0,5,7,0,0,1},
        {0,7,0,9,6,0,0,0,0},
        {0,9,0,7,0,4,0,1,0},
        {0,0,0,0,8,1,0,4,0},
        {6,0,0,2,4,0,0,8,0},
        {0,0,4,5,0,0,0,9,3},
        {5,0,0,0,0,0,0,0,0}
    };

    afisare(sudoku);
    printf("================================\n");
    if(solve(sudoku,0,0))
        afisare(sudoku);
    else 
        printf("\n\nEROARE\n\n");
    return 0;
}