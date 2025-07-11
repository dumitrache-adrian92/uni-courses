#include<stdio.h>
#include<stdlib.h>
struct nod
{
    int valoare;
    struct nod *stanga, *dreapta;
};

struct nod *creazaNod(int item)
{
    struct nod *temp = (struct nod *)malloc(sizeof(struct nod));
    temp->valoare = item;
    temp->stanga = temp->dreapta = NULL;
    return temp;
}
//parcurgere preordine
void preordine(struct nod *radacina)
{
    if (radacina != NULL)
    {
        printf("%d ", radacina->valoare);
        preordine(radacina->stanga);
        preordine(radacina->dreapta);
    }
}

// parcurgere inordine
void inordine(struct nod *radacina)
{
    if (radacina != NULL)
    {
        inordine(radacina->stanga);
        printf("%d ", radacina->valoare);
        inordine(radacina->dreapta);
    }
}

//parcurgere postordine
void postordine(struct nod *radacina)
{
    if (radacina != NULL)
    {
        postordine(radacina->stanga);
        postordine(radacina->dreapta);
        printf("%d ", radacina->valoare);
    }
}

struct nod* adaugaNod(struct nod* nod, int valoare)
{
    if (nod == NULL) return creazaNod(valoare);
    if (valoare < nod->valoare)
        nod->stanga = adaugaNod(nod->stanga, valoare);
    else
        nod->dreapta = adaugaNod(nod->dreapta, valoare);
    return nod;
}

struct nod * nodCuValoareMinima(struct nod* nod)
{
    struct nod* curent = nod;
    while (curent && curent->stanga != NULL)
        curent = curent->stanga;
    return curent;
}

struct nod* stergeNod(struct nod* radacina, int valoare)
{
    if (radacina == NULL) return radacina;
    if (valoare < radacina->valoare)
        radacina->stanga = stergeNod(radacina->stanga, valoare);
    else if (valoare > radacina->valoare)
        radacina->dreapta = stergeNod(radacina->dreapta, valoare);
    //daca radacina are valoarea pe care o cautam
    else
    {
        if (radacina->stanga == NULL)
        {
            struct nod *temp = radacina->dreapta;
            free(radacina);
            return temp;
        }
        else if (radacina->dreapta == NULL)
        {
            struct nod *temp = radacina->stanga;
            free(radacina);
            return temp;
        }
        // nod cu copil in partea stanga, cat si la dreapta. Gaseste elementul din subarborele drept care are cea mai mica valoare
        struct nod* temp = nodCuValoareMinima(radacina->dreapta);
        radacina->valoare = temp->valoare;
        radacina->dreapta = stergeNod(radacina->dreapta, temp->valoare);
    }
    return radacina;
}

void nivelK(struct nod *radacina, int k, int i, int *sum)
{
    if (radacina != NULL)
    {
        nivelK(radacina->stanga, k, i + 1, sum);
        nivelK(radacina->dreapta, k, i + 1, sum);
        if (k == i)
            *sum += radacina->valoare;
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
    radacina = adaugaNod(radacina, 50);
    radacina = adaugaNod(radacina, 30);
    radacina = adaugaNod(radacina, 20);
    radacina = adaugaNod(radacina, 40);
    radacina = adaugaNod(radacina, 70);
    radacina = adaugaNod(radacina, 60);
    radacina = adaugaNod(radacina, 80);
    int sum = 0;
    nivelK(radacina, 2, 0, &sum);
    printf("%d\n", sum);
    return 0;
}