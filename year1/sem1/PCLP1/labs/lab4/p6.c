#include <stdio.h>
// Se citeşte o matrice pătratică A de la tastatură.
// Afişati toate elementele de sub diagonala secundară, pe coloane.

void main()
{
    int n, i, j;
    scanf("%d", &n);
    int a[n][n];
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &a[i][j]);
    for (j = 1; j < n; j++)
        for (i = n - j; i < n; i++)
            printf("%d ", a[i][j]);
    printf("\n");
}