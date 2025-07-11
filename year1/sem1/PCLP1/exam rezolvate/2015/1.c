#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nume[30];
    float pret;
} Produs;

void creare(char *fisier, Produs **mega, int *nr) {
    FILE *f = fopen(fisier, "rb");
    fread(nr, sizeof(int), 1, f);
    *mega = malloc(*nr * sizeof(Produs));
    fread(*mega, sizeof(Produs), *nr, f);
    fclose(f);
}

int cmpDen(const void *p1, const void *p2) {
    Produs *x = (Produs *)p1, *y = (Produs *)p2;
    return strcmp(x->nume, y->nume);
}

float cauta(Produs *v, int nr, char *nume, int (*cmp)(const void *, const void *)) {
    Produs *aux, aux2;
    strcpy(aux2.nume, nume);
    qsort(v, nr, sizeof(Produs), cmp);
    aux = bsearch(&aux2, v, nr, sizeof(Produs), cmp);
    if (aux == NULL)
        return -1;
    else
        return aux->pret;
}

int main(int argc, char **argv) {
    char nume[30];
    fgets(nume, 30, stdin);
    nume[strlen(nume)-1] = '\0';
    Produs *carrefour;
    int nr;
    creare(argv[1], &carrefour, &nr);
    printf("%g", cauta(carrefour, nr, nume, cmpDen));
    free(carrefour);
}