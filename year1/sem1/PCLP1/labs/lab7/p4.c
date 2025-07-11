#include <stdio.h>
#include <string.h>

char *substr(char *src, int n, char *dest)
{
    dest = strncpy(dest, src, n);
    return dest;
}

void main()
{
    char s[101], dest[101];
    int n, p;
    fgets(s, 101, stdin);
    scanf("%d%d", &n, &p);
    substr(s + n, p, dest);
    puts(dest);
}
