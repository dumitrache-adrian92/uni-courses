#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    int n, *v, i, j, k;
    char **cuvinte, sir[20];
    scanf("%d", &n);
    v = calloc(n, sizeof(int));
    cuvinte = malloc(n * sizeof(char *));
    k = 0;
    for (i = 0; i < n; i++)
    {
        scanf("%s", sir);
        for (j = 0; j < k; j++)
        {
            if (strcmp(cuvinte[j], sir) == 0)
            {
                v[j]++;
                break;
            }
        }
        if (j == k)
        {
            cuvinte[k] = malloc(strlen(sir) + 1);
            strcpy(cuvinte[k], sir);
            v[k] = 1;
            k++;
        }
    }
    for (i = 0; i < k; i++)
        printf("%s %d\n", cuvinte[i], v[i]);
    free(v);
    free(cuvinte);
}