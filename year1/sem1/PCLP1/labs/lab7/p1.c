#include <stdio.h>

void swap(int *pa, int *pb);

void main()
{
    int a, b;
    scanf ("%d%d", &a, &b);
    swap(&a, &b);
    printf("%d %d\n", a, b);
}

void swap(int *pa, int *pb)
{
    *pa = *pa + *pb;
    *pb = *pa - *pb;
    *pa = *pa - *pb;
}