#include <stdio.h>
// Să se afişeze toate numerele naturale mai mici decât n care se pot scrie în două moduri diferite ca sumă de pătrate.
void main()
{
    int n, v[1000] = {0};
    int i, j;
    i = 1;
    j = 1;
    scanf("%d", &n);
    while (i * i < n)
    {
        while (i * i + j * j < n)
        {
            v[i * i + j * j]++;
            j++;
        }
        i++;
        j = i;
    }
    for (i = 1; i <= n; i++)
        if (v[i] == 2)
            printf("%d ", i);
    printf("\n");
}