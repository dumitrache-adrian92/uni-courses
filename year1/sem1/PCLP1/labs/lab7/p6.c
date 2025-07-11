#include <stdio.h>
#include <string.h>
char *next(char *from, char *word)
{
    int i, j;
    for (i=0;i<strlen(from);i++)
        if (from[i]>='a' && from[i]<='z')
            break;
    for (j=i;j<strlen(from);j++)
        if (from[j]<'a' || from[j]>'z')
            break;
    strncpy (word, from+i, j-i);
    word[j-i]='\0';
    return from+j;
}

void main()
{
    char s[101], word[101], *p;
    fgets(s, 101, stdin);
    p=next (s, word);
    while(p-s<strlen(s))
    {
        printf ("%s ", word);
        p=next (p, word);
    }
}