#include <stdio.h> 

void main() 
{ 
     float x, y;
     scanf("%f%f", &x, &y);
     if (x==0 || y==0)
        printf("punct pe axe\n");
     else if (x>0)
        if (y>0)
            printf("1\n");
        else
            printf("2\n");
    else if (y<0)
        printf("3\n");
    else
        printf("4\n");
}