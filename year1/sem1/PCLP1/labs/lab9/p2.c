#include <stdio.h>
#include <time.h>

void main()
{
    struct tm localTime;
    time_t rawTime;
    time(&rawTime);
    localTime = *localtime(&rawTime);
    printf("Suntem in data de %02d.%02d.%d si este ora %02d:%02d:%02d.\n",
           localTime.tm_mday, localTime.tm_mon,
           1900 + localTime.tm_year, localTime.tm_hour,
           localTime.tm_min, localTime.tm_sec);
}