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
    int x, min;
    do {
        printf("Introduceti un numar (Introduceti 0 pentru a iesi)\n");
        scanf("%d", &x);
        if (x == 0)
            break;
        push(&headMain, x);
    } while (x);
    min = headMain->x;
    list *i = headMain, *p;
    ;
    while (i) {
        if (i->x < min)
            min = i->x;
        if (i->x < 0) {
            p = i;
            if (headMain == i)
                headMain = i->next;
            if (i->next != NULL)
                i->next->previous = i->previous;
            if (i->previous != NULL)
                i->previous->next = i->next;
            i = i->next;
            free(p);
        } else
            i = i->next;
    }
    printf("%d\n", min);
    printList(headMain);
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