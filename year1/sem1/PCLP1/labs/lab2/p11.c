#include <stdio.h>
#include <math.h>
void main() 
{ 
    float a, b, c;
    float delta, s1, s2;
    scanf("%f%f%f",&a,&b,&c);
    if (a==0 && b==0 && c==0)
    {
        printf("Infinit");
        return;
    }    
    delta=b*b-4*a*c;
    if (delta<0)
    {
        printf("Nu exista solutii\n");
        return;
    }    
    s1=(-1*b-sqrt(delta))/(2*a);
    s2=(-1*b+sqrt(delta))/(2*a);
    if (delta==0)
        printf("%f\n", s1);
    else
        printf("%f %f\n", s1, s2);
}