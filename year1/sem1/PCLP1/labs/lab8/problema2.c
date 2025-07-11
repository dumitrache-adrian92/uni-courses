#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    int *v, cap, n, x, i;
    cap = 5;
    n = 0;
    v = malloc(cap * sizeof(int));
    scanf("%d", &x);
    while (x != 0)
    {
        v[n] = x;
        n++;
        if (n == cap)
        {
            cap*=2;
            v = realloc(v, cap * sizeof(int));
        }
        scanf("%d", &x);
    }
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}