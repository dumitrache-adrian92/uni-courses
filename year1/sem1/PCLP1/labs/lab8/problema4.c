#include <stdio.h>
#include <stdlib.h>

void main()
{
    long int *v1, *v2;
    int n, k, i, j;
    scanf("%d%d", &n, &k);
    v1 = calloc(n + 1, sizeof(long int));
    v2 = calloc(n + 1, sizeof(long int));
    v1[0] = v1[1] = v2[0] = 1;
    for (i = 2; i <= n; i++)
        if (i % 2 == 0)
        {
            for (j = 1; j <= k; j++)
            {
                v2[j] = v1[j - 1] + v1[j];
            }
        }
        else
            for (j = 1; j <= k; j++)
            {
                v1[j] = v2[j - 1] + v2[j];
            }
    if (n % 2 == 0)
        printf("%ld\n", v2[k]);
    else
        printf("%ld\n", v1[k]);
    free(v1);
    free(v2);
}