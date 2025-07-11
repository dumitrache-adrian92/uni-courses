#include <stdio.h>
// Interclasarea a 2 vectori

void main()
{
    int v1[100], v2[100], n, m, i, j;
    int v3[200], k;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &v1[i]);
    scanf("%d", &m);
    for (i = 0; i < m; i++)
        scanf("%d", &v2[i]);
    i = j = 0;
    k = 0;
    while (i < n && j < m)
        if (v1[i] < v2[j])
        {
            v3[k] = v1[i];
            k++;
            i++;
        }
        else if (v1[i] > v2[j])
        {
            v3[k] = v2[j];
            k++;
            j++;
        }
        else
        {
            v3[k] = v1[i];
            k++;
            v3[k] = v2[j];
            k++;
            i++;
            j++;
        }
    while (i < n)
    {
        v3[k] = v1[i];
        k++;
        i++;
    }
    while (j < m)
    {
        v3[k] = v2[j];
        k++;
        j++;
    }
    for (i = 0; i < k; i++)
        printf("%d ", v3[i]);
    printf("\n");
}