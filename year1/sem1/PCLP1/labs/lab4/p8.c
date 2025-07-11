#include <stdio.h>
// Program pentru afişarea secvenţei de elemente consecutive de sumă maximă dintr-un vector.

void main()
{
    int n, i;
    int max, maxStart, maxEnd, curent, curentStart;
    scanf("%d", &n);
    int v[n];
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);
    max = curent = v[0];
    maxStart = maxEnd = curentStart = 0;
    for (i = 1; i < n; i++)
    {
        curent += v[i];
        if (curent > max)
        {
            max = curent;
            maxStart = curentStart;
            maxEnd = i;
        }
        if (curent < 0)
        {
            curentStart = i + 1;
            curent = 0;
        }
    }
    for (i = maxStart; i <= maxEnd; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}
