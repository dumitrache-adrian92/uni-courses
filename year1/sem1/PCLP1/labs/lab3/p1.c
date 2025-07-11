#include <stdio.h>
// Scrieţi un program pentru afişarea codurilor tuturor caracterelor cu coduri între 32 şi 127,
// folosind funcţia printf într-un ciclu, câte zece caractere pe o linie.

void main()
{
    int nr;
    nr = 0;
    for (int ch = 32; ch <= 127; ch++)
    {
        if (nr == 10)
        {
            printf("\n");
            nr = 0;
        }
        printf("%c = %d ", ch, ch);
        nr++;
    }
    printf("\n");
}