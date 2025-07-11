#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int equal(char a, char b)
{
    if (a == b || fabs(a - b) == 'a' - 'A')
        return 1;
    return 0;
}

void main()
{
    int n, i, x;
    char *sir, cuvant[100];
    x = 100;
    sir = malloc(x);
    scanf("%d", &n);
    scanf("%s", sir);
    for (i = 1; i < n; i++)
    {
        scanf("%s", cuvant);
        if (equal(cuvant[0], sir[strlen(sir) - 2]) && equal(cuvant[1], sir[strlen(sir) - 1]))
        {
            if (strlen(sir) + strlen(cuvant) + 3 > x)
            {
                x *= 2;
                sir = realloc(sir, x);
            }
            strcat(sir, "-");
            strcat(sir, cuvant);
        }
    }
    puts(sir);
}