#include <stdio.h>
#include <math.h>

float dist(int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void main()
{
    int n, p1, p2;
    float max = 0;
    scanf("%d", &n);
    int x[n], y[n], i, j;
    for (i = 0; i < n; i++)
        scanf("%d%d", &x[i], &y[i]);
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (dist(x[i], y[i], x[j], y[j]) > max)
            {
                max = dist(x[i], y[i], x[j], y[j]);
                p1 = i;
                p2 = j;
            }
    printf("%d %d\n", x[p1], y[p1]);
    printf("%d %d\n", x[p2], y[p2]);
    printf("%.7g\n", max);
}