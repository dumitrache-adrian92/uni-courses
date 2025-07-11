#include <stdio.h>
#include <string.h>

char *strdel(char *p, int n)
{
    strcpy(p, p + n);
}

char *strins(char *p, char *s)
{
    char aux[3001];
    strcpy(aux, p);
    strcpy(p, s);
    strcat(p, aux);
}

void main()
{
    char text[3001], vechi[21], nou[21], *p;
    fgets(text, 3001, stdin);
    text[strlen(text) - 1] = '\0';
    fgets(vechi, 21, stdin);
    vechi[strlen(vechi) - 1] = '\0';
    fgets(nou, 21, stdin);
    nou[strlen(nou) - 1] = '\0';
    p = strstr(text, vechi);
    do
    {
        strdel(p, strlen(vechi));
        strins(p, nou);
    } while(p=strstr(p+strlen(nou), vechi));
    puts(text);
}