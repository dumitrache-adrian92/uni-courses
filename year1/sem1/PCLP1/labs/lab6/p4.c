#include <stdio.h>

int strcmp(char *a, char *b)
{
    int i, result;
    i = 0;
    result = 0;
    while (result == 0 && a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] > b[i])
            result = 1;
        else if (a[i] < b[i])
            result = -1;
        i++;
    }
    if (result == 0)
    {
        if (b[i] != '\0')
            if (a[i] == '\0')
                return -1;
        if (a[i] != '\0')
            if (b[i] == '\0')
                return 1;
    }
    return result;
}

void main()
{
    char a[100], b[100];
    fgets(a, 100, stdin);
    fgets(b, 100, stdin);
    printf("%d\n", strcmp(a, b));
}