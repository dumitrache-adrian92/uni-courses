#include <stdio.h>
#include <string.h>

int cmp314cc(char *x, char *y) {
    for (int i = 0; x[i] != '\0' || y[i] != '\0'; i++) {
        if (x[i]!=y[i])
            return x[i]-y[i];
    }
    return 0;
}

char * next(char *adr, char *num) {
    int i = 0, j = 0;
    char a[100]="qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
    while (adr[i] != NULL && strchr(a, adr[i])==NULL)
        i++;
    if (adr[i]==NULL)
        return NULL;
    j = i+1;
    while (adr[j] != NULL && strchr(a, adr[j])==NULL)
        j++;
    if (adr[j]==NULL)
        strcpy(num, adr+i);
    else
        strncpy(num, adr+i, j);
    return num;
}

int main() {
    char str[30]="muie", str2[30]="muie";
    printf("%d", cmp314cc(str, str2));
}