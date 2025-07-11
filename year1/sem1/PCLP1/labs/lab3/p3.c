#include <stdio.h>
// Scrieţi un program care adună de n ori x şi de n ori y.
// Se vor afişa la fiecare n/10 termeni calculaţi sumele parţiale
// şi se vor folosi ambele formate de afişare: %f şi %e.

void main()
{
    int n;
    float x, sx;
    double y, sy;
    sx = sy = 0;
    scanf("%d%f%lf", &n, &x, &y);
    for (int i = 1; i <= n; i++)
    {
        sx += x;
        sy += y;
        if (i % (n / 10) == 0)
            printf("%f %e %f %e\n", sx, sx, sy, sy);
    }
}