#include <stdio.h>
#include <math.h>

void unghiuri(float ab, float bc, float ac, float *A, float *B, float *C)
{
    *A = 180 * acos((pow(ac, 2) + pow(ab, 2) - pow(bc, 2)) / (2 * ab * ac)) / M_PI;
    *B = 180 * acos((pow(bc, 2) + pow(ab, 2) - pow(ac, 2)) / (2 * ab * bc)) / M_PI;
    *C = 180.0 - *A - *B;
}

void main()
{
    float ab, bc, ac, A, B, C;
    scanf("%f%f%f", &ab, &bc, &ac);
    unghiuri(ab, bc, ac, &A, &B, &C);
    printf("%.3f %.3f %.3f\n", A, B, C);
}