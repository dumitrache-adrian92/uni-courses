#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct nod
{
    char valoare[10];
    struct nod *stanga, *dreapta;
};

void adaugaNod(struct nod *radacina, int stgDr, char *valoare)
{
    struct nod *temp = (struct nod *)malloc(sizeof(struct nod));
    strcpy(temp->valoare, valoare);
    temp->stanga = temp->dreapta = NULL;
    if (radacina == NULL)
        radacina = temp;
    else if (stgDr == 0)
        radacina->stanga = temp;
    else
        radacina->dreapta = temp;
}


void preordine(struct nod *radacina)
{
    if (radacina != NULL)
    {
        //puts(radacina->valoare);
        preordine(radacina->stanga);
        preordine(radacina->dreapta);
    }
}

int main()
{
    /* Consideram urmatorul arbore binar
          50
        /   \
       30   70
      / \   / \
    20  40 60 80 */
    struct nod *radacina = NULL;
    adaugaNod(radacina, 0, "+");
    adaugaNod(radacina, 0, "*");
    adaugaNod(radacina, 1, "-");
    /* if (radacina->stanga!=NULL)
        printf("lol"); */
    /* adaugaNod(radacina->stanga, 0, "5");
    adaugaNod(radacina->stanga, 1, "4");
    adaugaNod(radacina->dreapta, 0, "100");
    adaugaNod(radacina->dreapta, 1, "/");
    adaugaNod(radacina->dreapta->dreapta, 0, "20");
    adaugaNod(radacina->dreapta->dreapta, 1, "2"); */
    //preordine(radacina);
    return 0;
}


