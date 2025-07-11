#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int n, m;
    int **a;
} MATRICE;

MATRICE *creeaza_MATRICE(int n, int m)
{
    MATRICE *x;
    x = malloc(sizeof(MATRICE));
    x->n = n;
    x->m = m;
    x->a = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        x->a[i] = calloc(m, sizeof(int));
    return x;
}

// nu inteleg de ce mai returnam adresa matricei daca oricum o transmitem ca parametru
MATRICE *citeste_MATRICE(MATRICE *ma)
{
    for (int i = 0; i < ma->n; i++)
        for (int j = 0; j < ma->m; j++)
            scanf("%d", &ma->a[i][j]);
    return ma;
}

void scrie_MATRICE(MATRICE *ma)
{
    for (int i = 0; i < ma->n; i++)
    {
        for (int j = 0; j < ma->m; j++)
            printf("%d ", ma->a[i][j]);
        printf("\n");
    }
}

MATRICE *aduna_MATRICE(MATRICE *ma, MATRICE *mb)
{
    if (ma->n != mb->n || ma->m != mb->m)
        return NULL;
    MATRICE *mc;
    mc = creeaza_MATRICE(ma->n, ma->m);
    for (int i = 0; i < ma->n; i++)
        for (int j = 0; j < mb->m; j++)
            mc->a[i][j] = ma->a[i][j] + mb->a[i][j];
    return mc;
}

MATRICE* inmulteste_MATRICE(MATRICE* ma, MATRICE* mb)
{
    if (ma->m != mb->n)
        return NULL;
    MATRICE *mc;
    mc = creeaza_MATRICE (ma->n, mb->m);
    for (int i = 0; i < ma->n; i++)
    {
        for (int j = 0; j < mb->m; j++)
            for (int k = 0; k < ma->m; k++)
                mc->a[i][j] += ma->a[i][k] * mb->a[k][j];
    }
    return mc;
}

void main()
{
    MATRICE *ma, *mb, *mc;
    int i, j;
    scanf("%d%d", &i, &j);
    ma = creeaza_MATRICE(i, j);
    mb = creeaza_MATRICE(i, j);
    citeste_MATRICE(ma);
    citeste_MATRICE(mb);
    mc = aduna_MATRICE(ma, mb);
    scrie_MATRICE(mc);
    mc = inmulteste_MATRICE(ma, mb);
    scrie_MATRICE(mc);
}