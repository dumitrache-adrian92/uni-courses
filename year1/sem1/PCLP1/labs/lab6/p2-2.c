#include <stdio.h>
#include <math.h>

void unghiuri(float *lat, float *ung)
{
    ung[0] = 180 * acos((pow(lat[2], 2) + pow(lat[0], 2) - pow(lat[1], 2)) / (2 * lat[0] * lat[2])) / M_PI;
    ung[1] = 180 * acos((pow(lat[1], 2) + pow(lat[0], 2) - pow(lat[2], 2)) / (2 * lat[0] * lat[1])) / M_PI;
    ung[2] = 180.0 - ung[0] - ung[1];
}

void main()
{
    float lat[3], ung[3];
    scanf("%f%f%f", &lat[0], &lat[1], &lat[2]);
    unghiuri(lat, ung);
    printf("%.3f %.3f %.3f\n", ung[0], ung[1], ung[2]);
}