#include <stdio.h>

void count(int n, int *v, int *zero, int *poz, int *neg)
{
    *zero = *poz = *neg = 0;
    for (int i = 0; i < n; i++)
        if (v[i] < 0)
            (*neg)++;
        else if (v[i] > 0)
            (*poz)++;
        else
            (*zero)++;
}

void main()
{
    int n, zero, neg, poz;
    scanf("%d", &n);
    int v[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    count(n, v, &zero, &poz, &neg);
    printf("nule:%d\npozitive:%d\nnegative:%d\n", zero, poz, neg);
}
