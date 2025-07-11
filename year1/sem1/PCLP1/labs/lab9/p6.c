#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    int n, k, i, j, cap;
    char sir[20];
    struct cuvant
    {
        char *cuv;
        int ap;
    } * cuvinte;
    k = 0;
    cap = 30;
    cuvinte = malloc(cap * sizeof(struct cuvant));
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%s", sir);
        for (j = 0; j < k; j++)
        {
            if (strcmp(cuvinte[j].cuv, sir) == 0)
            {
                cuvinte[j].ap++;
                break;
            }
        }
        if (j == k)
        {
            cuvinte[k].cuv = malloc(strlen(sir) + 1);
            strcpy(cuvinte[k].cuv, sir);
            cuvinte[k].ap = 1;
            k++;
        }
        if (k == cap)
        {
            cap *= 2;
            cuvinte = realloc(cuvinte, cap * sizeof(struct cuvant));
        }
    }
    for (i = 0; i < k; i++)
        printf("%s %d\n", cuvinte[i].cuv, cuvinte[i].ap);
    free(cuvinte);
}