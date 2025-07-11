#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *my_replace(char *s, char *s1, char *s2)
{
    char *p = malloc(10000 * sizeof(char));
    p = strdup(s);
    *(p + (strstr(s, s1) - s)) = '\0';
    strcat(p, s2);
    strcat(p, s + (strstr(s, s1) - s) + strlen(s1));
    strcpy(s, p);
    free(p);
}

void main()
{
    char s[101], s1[101], s2[101];
    scanf("%s %s", s1, s2);
    getchar();
    fgets(s, 101, stdin);
    s[strlen(s) - 1] = '\0';
    while (strstr(s, s1) != NULL)
        my_replace(s, s1, s2);
    puts(s);
}