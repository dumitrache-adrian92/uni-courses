#include <stdio.h>
#include <string.h>
#define MAX 3
struct MATERIA {
    char nume[16], tip_examen;
    int ore_curs;
};

void citire_MAT (struct MATERIA *m)
{
    int OK=0, i;
    printf("Nume materie: ");
    while (!OK)
    {
        fgets (m->nume, 16, stdin);
        m->nume[strlen(m->nume)-1]='\0';
        OK=1;
        for (i=0; i<strlen(m->nume); i++)
            if (m->nume[i]!=' ' && !(m->nume[i]>='a' && m->nume[i]<='z') && !(m->nume[i]>='A' && m->nume[i]<='Z'))
            {
                OK=0;
                break;
            }
        if (OK==0)
            printf ("Numele materiei trebuie sa contina doar litere si spatii. Introduceti alt nume: ");
    }
    printf("Numar ore: ");
    scanf ("%d", &m->ore_curs);
    while (m->ore_curs<=0)
    {
        printf ("Numarul de ore trebuie sa fie strict pozitiv. Introduceti alt numar: ");
        scanf ("%d", &m->ore_curs);
    }
    printf("Tipul de examen: ");
    scanf (" %c", &m->tip_examen);
    while (m->tip_examen!='C' && m->tip_examen!='S' && m->tip_examen!='A')
    {
        printf ("Tipul de examen poate fi doar C, S sau A. Introduceti alt tip de examen: ");
        scanf (" %c", &m->tip_examen);
    }
}

void citire_PROGRAMA (struct MATERIA *PROGRAMA)
{
    for (int i=0; i<MAX; i++)
    {
        citire_MAT(&PROGRAMA[i]);
        getchar();
    }
}

void afisare (struct MATERIA *PROGRAMA, char c, int x)
{
    for (int i=0; i<MAX; i++)
        if (PROGRAMA[i].tip_examen==c && PROGRAMA[i].ore_curs==x)
        {
            puts (PROGRAMA[i].nume);
            printf("%c\n%d\n", PROGRAMA[i].tip_examen, PROGRAMA[i].ore_curs);
        }
}

void main()
{
    struct MATERIA PROGRAMA[MAX];
    citire_PROGRAMA(PROGRAMA);
    afisare (PROGRAMA, 'A', 5);
}