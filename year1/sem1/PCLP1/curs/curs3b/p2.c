#include <stdio.h>
// Program pentru citirea unui vector de întregi
// şi extragerea elementelor distincte într-un al doilea vector, care se va afişa.

void main()
{
    int a[100], n, i;
    int b[100], m, j;
    int OK;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    m = 0;
    for (i = 0; i < n; i++)
    {
        OK = 1;
        for (j = 0; j < m; j++)
            if (a[i] == b[j])
                OK = 0;
        if (OK)
        {
            b[m] = a[i];
            m++;
        }
    }
    for (j = 0; j < m; j++)
        printf("%d ", b[j]);
    printf("\n");
}