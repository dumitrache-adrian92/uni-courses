#include <stdio.h> 
#include <math.h> 
 
int main() 
{ 
     double x, PI = M_PI;
     printf("|       x|  sin(x)|  cox(x)|\n");
     for (x = 0; x <= 2 * PI; x = x + PI / 10) {
          printf("|%8.2lf|%lf|%lf|\n", x, sin(x), cos(x)); 
     }
     getchar(); 
     return 0; 
}