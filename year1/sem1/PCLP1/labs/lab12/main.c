#include "Produs.h"

void productGen(char *numeFisier) {
    FILE *f;
    produs p;
    int x;
    f = fopen(numeFisier, "wb+");
    if (!f)
        return;
    srand(time(0));
    for (int i = 0; i < 100; i++) {
        x = rand();
        p.cantitate = x % 100;
        p.pret_produs = x <= 100 ? x : x % 100;
        sprintf(p.nume_produs, "Produs%d", x);
        fwrite(&p, sizeof(produs), 1, f);
    }
    fclose(f);
}

void afisareEcran(char *numeFisier) {
    produs p;
    FILE *f;
    f = fopen(numeFisier, "rb+");
    for (int i = 0; i < 100; i++) {
        fread(&p, sizeof(produs), 1, f);
        printf("%s %d %lg\n", p.nume_produs, p.cantitate, p.pret_produs);
    }
    fclose(f);
}

void sort(char *numeFisier) {
    produs p[100], aux;
    FILE *f;
    f = fopen(numeFisier, "rb+");
    fread(p, sizeof(produs), 100, f);
    for (int i = 0; i < 99; i++)
        for (int j = i + 1; j < 100; j++)
            if (strcmp(p[i].nume_produs, p[j].nume_produs) > 0) {
                aux = p[i];
                p[i] = p[j];
                p[j] = aux;
            }
    fclose(f);
    f=fopen(numeFisier,"wb+");
    fwrite(p, sizeof(produs), 100, f);
    fclose(f);
}

void cautare(char *numeFisier, char *input) {
    int i;
    produs p;
    FILE *f;
    f = fopen(numeFisier, "rb");
    for (i = 0; i < 100; i++) {
        fread(&p, sizeof(produs), 1, f);
        if(strcmp(input, p.nume_produs)==0) {
            printf("%s %d %lg\n", p.nume_produs, p.cantitate, p.pret_produs);
            break;
        }
    }
    if (i==100)
        printf("N-am gasit.\n");
    fclose(f);
}

void suprascriere(char *numeFisier, char *input) {
    int i;
    produs p, aux;
    FILE *f;
    strcpy(aux.nume_produs, "nouNume");
    aux.pret_produs=10;
    aux.cantitate=100;
    f = fopen(numeFisier, "rb+");
    for (i = 0; i < 100; i++) {
        fread(&p, sizeof(produs), 1, f);
        if(strcmp(input, p.nume_produs)==0) {
            fseek(f, i*sizeof(produs), SEEK_SET);
            fwrite(&aux, sizeof(produs), 1, f);
            break;
        }
    }
    if (i==100)
        printf("N-am gasit.\n");
    fclose(f);
}

void main(int argc, char **argv) {
    productGen("test");
    //afisareEcran("test");
    //sort("test");
    //afisareEcran("test");
    //cautare("test", "Produs2");
    //suprascriere("test", "Produs98");
    afisareEcran("test");
}