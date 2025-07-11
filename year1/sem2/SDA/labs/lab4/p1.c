#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int value;
    struct Node *previous;
    struct Node *next;
} node;

typedef struct {
    node *start;
    node *end;
} dlist;

int emptyList(dlist x) {
    if (!x.start)
        return 1;
    return 0;
}

void initList(dlist *x) {
    x->start = x->end = NULL;
}

void pushTail(dlist *x, int value) {
    node *aux = (node *)malloc(sizeof(node));
    aux->value = value;
    aux->previous = x->end;
    aux->next = NULL;
    x->end = aux;
    if (emptyList(*x))
        x->start = aux;
    else
        aux->previous->next = aux;
}


void readList(dlist *x) {
    initList(x);
    int value;
    scanf("%d", &value);
    pushTail(x, value);
    scanf("%d", &value);
    pushTail(x, value);
    do {
        scanf("%d", &value);
        pushTail(x, value);
    } while(value != x->end->previous->value + x->end->previous->previous->value);
}

void printList(dlist x) {
    for (node *i = x.end; i != NULL; i = i->previous)
        printf("%d ", i->value);
    printf("\n");
}

int main() {
    dlist x;
    readList(&x);
    printList(x);
}