#include <stdio.h>
#include <string.h>


int hashFunction(char *user) {
    int i, sum = 0;
    for (i = 0; i < strlen(user); i++)
        sum = sum + (i + 1) * user[i];
    return sum % 100;
}

int main() {
    char user[100], pass[100];
    char hash[100][100];
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%s %s", user, pass);
        strcpy(hash[hashFunction(user)], pass);
    }

    printf("login:\n");

    scanf("%s %s", user, pass);
    if(strcmp(hash[hashFunction(user)], pass) == 0)
        printf("welcome\n");
    else
        printf("WRONG\n");
}