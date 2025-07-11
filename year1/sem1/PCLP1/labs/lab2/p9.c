#include <stdio.h> 

void main() 
{ 
    int h, m, s;
    scanf("%d%d%d", &h, &m, &s);
    if (h<10)
        printf("0");
    printf("%d:", h);
    if (m<10)
        printf("0");
    printf("%d:", m);
    if (s<10)
        printf("0");
    printf("%d\n", s);
}