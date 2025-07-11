#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void itoa(int x, char s[])
{
    int k, i, aux;
    k = 0;
    while (x != 0)
    {
        s[k] = '0' + x % 10;
        x /= 10;
        k++;
    }
    s[k] = '\0';
    for (i = 0; i < k / 2; i++)
    {
        aux = s[i];
        s[i] = s[k - i - 1];
        s[k - i - 1] = aux;
    }
}

char *timestr(struct tm t, char *time)
{
    char s[10];
    itoa(t.tm_hour, s);
    strcpy(time, s);
    strcat(time, ":");
    itoa(t.tm_min, s);
    strcat(time, s);
    strcat(time, ":");
    itoa(t.tm_sec, s);
    strcat(time, s);
}

void main()
{
    char sir[20];
    struct tm localTime;
    time_t rawTime;
    time(&rawTime);
    localTime = *localtime(&rawTime);
    timestr(localTime, sir);
    puts(sir);
}