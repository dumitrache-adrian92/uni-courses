#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

typedef struct Persoana {
    char *nume;
    char *prenume;
} Persoana;

void serializeaza(Persoana v[], int nrPersoane, char *fileName) {
    FILE *f = fopen(fileName, "wb");
    int x;
    for (int i = 0; i < N; i++) {
        x=strlen(v[i].nume);
        fwrite(&x, sizeof(int), 1, f);
        fwrite(v[i].nume, sizeof(v[i].nume), 1, f);
        x=strlen(v[i].prenume);
        fwrite(&x, sizeof(int), 1, f);
        fwrite(v[i].prenume, sizeof(v[i].prenume), 1, f);
    }
    fclose(f);
}

void deserializeaza(Persoana v[], int nrPersoane, char *fileName) {
    FILE *f = fopen(fileName, "rb");
    int x;
    for (int i = 0; i < N; i++) {
        fread(&x, sizeof(int), 1, f);
        v[i].nume = malloc(x + 1);
        fread(v[i].nume, sizeof(v[i].nume), 1, f);
        fread(&x, sizeof(int), 1, f);
        v[i].prenume = malloc(x + 1);
        fread(v[i].prenume, sizeof(v[i].prenume), 1, f);
    }
    fclose(f);
}

int main() {
    Persoana v[N], w[N];
    char *prenume[N] = {"Eric", "Kyle", "Stan", "Kenny"};
    char *nume[N] = {"Cartman", "Broflovski", "Marsh", "McCormick"};
    int i;
    for (i = 0; i < N; i++) {
        v[i].nume = nume[i];
        v[i].prenume = prenume[i];
    }

    // Serializam vectorul intr-un fisier
    serializeaza(v, N, "persoane.bin");
    // Deserializam in alt vector, din acelasi fisier. Ar trebui sa obtinem aceleasi informatii.
    deserializeaza(w, N, "persoane.bin");

    for (i = 0; i < N; i++) {
        printf("%s %s\n", w[i].prenume, w[i].nume);
    }

    return 0;
}