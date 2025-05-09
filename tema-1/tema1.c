#include "stdio.h"
#include "string.h"

typedef struct{
    char nume[10];
    char prenume[20];
    char localitate[12];
    char liceu[45];
    char hobbyuri[5][20];
    int nr_hobby;
}DATE;
void afisare(DATE date)
{
    printf("Nume:\t\t%s\nPrenume:\t%s\nOras:\t\t%s\nLiceu:\t\t%s\nHobby-uri:\n",date.nume,date.prenume,date.localitate,date.liceu);
    for(int i = 0; i < date.nr_hobby; i++)
    {
        printf("\t\t%s\n",date.hobbyuri[i]);
    }
}
void ordonare(char v_cuv[][20],int dimensiune)
{   
    char aux[20];
    for(int i = 0; i < dimensiune - 1; i++)
    for(int j = i + 1; j < dimensiune; j++)
    {
        if (strcmp(v_cuv[i],v_cuv[j]) > 0)
        {
            strcpy(aux,v_cuv[i]);
            strcpy(v_cuv[i],v_cuv[j]);
            strcpy(v_cuv[j],aux);
        }
    }
}

int main()
{
    DATE date_personale;
    strcpy(date_personale.nume, "Blidaru");
    strcpy(date_personale.prenume, "Andrei Eduard");
    strcpy(date_personale.localitate, "Targoviste");
    strcpy(date_personale.liceu,"Colegiul national \"Ienachita Vacarescu\"");
    strcpy(date_personale.hobbyuri[0],"Gaming");
    strcpy(date_personale.hobbyuri[1],"Construit Lego");
    strcpy(date_personale.hobbyuri[2],"Ascultare muzica");
    strcpy(date_personale.hobbyuri[3],"Codare");
    strcpy(date_personale.hobbyuri[4],"Youtube");
    date_personale.nr_hobby = 5;

    ordonare(date_personale.hobbyuri,date_personale.nr_hobby);
    afisare(date_personale);
    return 0;
}
