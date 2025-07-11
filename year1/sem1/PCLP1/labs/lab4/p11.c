#include <stdio.h>
#include <math.h>

void main()
{
    int n, c;
    float x, p1, p2;
    scanf("%f%d", &x, &n);
    p1 = p2 = 0;
    for (int i = n; i >= 0; i--)
    {
        scanf("%d", &c);
        p1 += pow(x, i) * c;
        p2 = p2 * x + c;
    }
    printf("%0.2f %0.2f\n", p1, p2);
}