#include <stdio.h>

void minmax(int *v, int n, int *min, int *max)
{
    *min = *max = v[0];
    for (int i = 1; i < n; i++)
    {
        if (v[i] < *min)
            *min = v[i];
        if (v[i] > *max)
            *max = v[i];
    }
}

void main()
{
    int n, v[100];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    int min, max;
    minmax(v, n, &min, &max);
    printf("%d %d\n", min, max);
}