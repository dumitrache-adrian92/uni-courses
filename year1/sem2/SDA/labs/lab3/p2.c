#include <stdio.h>
#include <stdlib.h>
typedef struct linkedList {
    int x;
    struct linkedList *next;
}list;

void createLinkedList(list *head);
void push(list **head, int x);
void printList(list *head);

int main() {
    list *headMain = NULL, *headOdd = NULL, *headEven = NULL;
    int x;
    do {
        printf("Introduceti un numar (Introduceti 0 pentru a iesi)\n");
        scanf("%d", &x);
        if (x == 0)
            break;
        push(&headMain, x);
    } while (x);
    x = 0;
    list *i = headMain;
    while(i) {
        if (x % 2 == 1)
            push(&headOdd, i->x);
        else
            push(&headEven, i->x);
        x++;
        i = i->next;
    }
    printList(headMain);
    printList(headEven);
    printList(headOdd);
    return 0;
}

void push(list **head, int x) {
    list *nou = malloc(sizeof(list));
    nou->x = x;
    nou->next = *head;
    *head = nou;
}

void printList(list *head) {
    list *i = head;
    while (i != NULL) {
        printf("%d ", i->x);
        i = i->next;
    }
    printf("\n");
}