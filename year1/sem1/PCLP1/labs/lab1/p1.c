#include <stdio.h>
// Interschimbul valorilor a două variabile a şi b.

void main()
{
    int x, y;

    scanf("%d %d", &x, &y);

    x=x+y;
    y=x-y;
    x=x-y;

    printf("%d %d\n", x, y);
}