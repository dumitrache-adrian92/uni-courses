#include <stdio.h>
#include <stdlib.h>
typedef struct linkedList {
    int x;
    struct linkedList *next;
    struct linkedList *previous;
} list;

void push(list **head, int x);
void printList(list *head);

int main() {
    list *headMain = NULL;
    int x, n, m;
    do {
        printf("Introduceti un numar (Introduceti 0 pentru a iesi)\n");
        scanf("%d", &x);
        if (x == 0)
            break;
        push(&headMain, x);
    } while (x);
    list *i = headMain, *p;
    scanf("%d", &m);
    scanf("%d", &n);
    while (i && n) {
        if (i->x > m)
            n--;
        i = i->next;
    }
    if (!n)
        printf("%d\n", i->x);
    return 0;
}

void push(list **head, int x) {
    list *new = malloc(sizeof(list));
    new->x = x;
    new->next = (*head);
    new->previous = NULL;
    if (*head != NULL)
        (*head)->previous = new;
    *head = new;
}

void printList(list *head) {
    list *i = head;
    while (i != NULL) {
        printf("%d ", i->x);
        i = i->next;
    }
    printf("\n");
}