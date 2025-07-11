#include <stdio.h>

void bubbleSort(int *v, int n)
{
    int ok, i;
    ok = 1;
    while (ok)
    {
        ok = 0;
        for (i = 0; i < n - 1; i++)
            if (v[i] > v[i + 1])
            {
                v[i] = v[i] + v[i + 1];
                v[i + 1] = v[i] - v[i + 1];
                v[i] = v[i] - v[i + 1];
                ok = 1;
            }
    }
}

void main()
{
    int n;
    scanf("%d", &n);
    int v[n], i;
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);
    bubbleSort(v, n);
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}