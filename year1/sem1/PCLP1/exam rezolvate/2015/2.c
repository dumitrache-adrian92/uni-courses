#include <stdio.h>
#include <stdlib.h>

void f(int **mat, int n, int m, int *poz, int *nPoz, int *neg, int *nNeg) {
    *nPoz = *nNeg = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (mat[i][j] > 0) {
                poz[*nPoz] = mat[i][j];
                (*nPoz)++;
            } else if (mat[i][j] < 0) {
                neg[*nNeg] = mat[i][j];
                *nNeg += 1;
            }
        }
}

int main() {
    int **mat, n, m, *poz, *neg, nPoz, nNeg, i, j;
    scanf("%d%d", &n, &m);
    mat = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        mat[i] = malloc(m * sizeof(int));
    poz = malloc(n * m * sizeof(int));
    neg = malloc(n * m * sizeof(int));
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &mat[i][j]);
    f(mat, n, m, poz, &nPoz, neg, &nNeg);
    for (i = 0; i < nPoz; i++)
        printf("%d ", poz[i]);
    printf("\n");
    for (i = 0; i < nNeg; i++)
        printf("%d ", neg[i]);
    printf("\n");
    for (i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
    free(poz);
    free(neg);
}

/*
    pe prima linie se declara un vector cu 3 elemente de tip int
    si o variabila de tip int si li se acorda valori
    a doua linie este gresita deoarece incearca sa incrementeze un
    pointer care nu este modificabil, daca linia ar fi fost fara ++arr,
    se afisa 20, daca era arr+1, se afisa 30
*/