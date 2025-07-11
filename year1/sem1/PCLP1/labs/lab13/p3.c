#include "p3.h"

void printEntry(const entry *a) {
    char *x = (char *)a->key, *y = (char *)a->value;
    fputs(x, stdout);
    printf(" ");
    puts(y);
}

int compareKey(const void *key1, const void *key2) {
    char *s1 = (char *)key1, *s2 = (char *)key2;
    return strcmp(s1, s2);
}

int compareEntry(const void *e1, const void *e2) {
    entry *x = (entry **)e1, *y = (entry **)e2;
    return strcmp(x->key, y->key);
}

void main() {
    char input, buffer;
    map m;
    entry a, b;
    init(&m, 10);
    a.key = "lol";
    b.key = "kuie";
    printf("%d", compareEntry(&a, &b));
    printf("1. - Afisare dictionar.\n2. - Cauta cuvant in dictionar.\n3. - Adauga cuvant in dictionar.\n4. - Sterge cuvant din dictionar.\n5. - Sortare dictionar\n6. - Iesire din program\n");
    do{
        input = getc(stdin);
        while (buffer = getc(stdin) != '\n' && buffer != EOF);
        switch(input) {
            case '1':
                print(&m, printEntry);
            case '2':

            case '3':

            case '4':

            case '5':

        }
    }while (input!='6');
}