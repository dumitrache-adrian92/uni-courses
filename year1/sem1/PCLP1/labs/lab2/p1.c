#include <stdio.h>
#include <stdlib.h>

void main()
{
    int seed, n;
    scanf("%d", &seed);
    srand(seed);
    printf("%d %d %d\n", rand(), rand(), rand());
}