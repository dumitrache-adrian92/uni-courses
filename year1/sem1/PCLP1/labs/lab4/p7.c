#include <stdio.h>
// Program pentru afişarea celei mai lungi secvenţe de elemente consecutive
// ordonate crescător dintr-un vector de numere naturale.

void main()
{
    int n, i, v[101], secvCurenta, secvCurentaStart, secvMax, secvMaxStart, secvMaxFinal;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);
    secvMax = secvCurenta = 1;
    secvMaxStart = secvMaxFinal = secvCurentaStart = 0;
    for (i = 1; i < n; i++)
    {
        if (v[i - 1] <= v[i])
            secvCurenta++;
        else
        {
            if (secvCurenta > secvMax)
            {
                secvMax = secvCurenta;
                secvMaxStart = secvCurentaStart;
                secvMaxFinal = i - 1;
            }
            secvCurenta = 1;
            secvCurentaStart = i;
        }
    }
    for (i = secvMaxStart; i <= secvMaxFinal; i++)
        printf("%d ", v[i]);
    printf("\n");
}