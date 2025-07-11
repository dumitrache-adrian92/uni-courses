#include <stdio.h>

int cmmmc(int a, int b)
{
    int x = a, y = b;
    while (a != b)
        if (a > b)
            a -= b;
        else
            b -= a;
    return x * y / a;
}

void main()
{
    int x1, x2, y1, y2;
    int numitor;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    numitor = cmmmc(y1, y2);
    x1 *= numitor / y1;
    x2 *= numitor / y2;
    y1 = y2 = numitor;
    printf("%d %d\n%d %d\n", x1, y1, x2, y2);
}