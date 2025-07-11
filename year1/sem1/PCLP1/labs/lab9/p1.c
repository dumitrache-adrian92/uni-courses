#include <stdio.h>

void main()
{
    struct punct
    {
        float x, y;
    } p;
    scanf("%f%f", &p.x, &p.y);
    printf("(%.2f,%.2f)\n", p.x, p.y);
}