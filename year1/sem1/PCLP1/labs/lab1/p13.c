#include <stdio.h>
// Se dă o secvenţă de n numere întregi, ale căror valori sunt cuprinse în intervalul [0,100].
// Să se afişeze valorile care apar cel mai des. (se vor folosi vectori).

void main()
{
    int n, x, mx;
    int v[101] = {0}, i;
    scanf("%d", &n);
    mx = -1;
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        v[x]++;
        if (v[x] > mx)
            mx = v[x];
    }
    for (i = 0; i <= 100; i++)
        if (v[i] == mx)
            printf("%d ", i);
}