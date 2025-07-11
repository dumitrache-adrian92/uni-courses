#include <stdio.h> 

void main() 
{ 
    int h, m, s;
    if (scanf("%d%d%d", &h, &m, &s)!=3)
    {
        printf("Date incorect introduse!\n");
        return;
    }
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