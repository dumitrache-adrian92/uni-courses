#ifndef STDIO_H
#include <stdio.h>
#endif
#ifndef STDLIB_H
#include <stdlib.h>
#endif
#ifndef STRING_H
#include <string.h>
#endif
#ifndef TIME_H
#include <time.h>
#endif

typedef struct {
    char nume_produs[21];
    int cantitate;
    float pret_produs;
}produs;

void productGen(char *numeFisier);
void afisareEcran(char *numeFisier);
void sort(char *numeFisier);
void cautare(char *numeFisier, char *input);
void suprascriere(char *numeFisier, char *input);