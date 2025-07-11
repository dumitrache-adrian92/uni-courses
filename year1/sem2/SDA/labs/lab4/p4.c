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

void pushSorted(dlist *x, int value) {
    node *aux = (node *)malloc(sizeof(node)), *current;
    aux->value = value;
    if (emptyList(*x))
        x->start = x->end = aux;
    else if (value <= x->start->value) {
        aux->next = x->start;
        aux->next->previous = aux;
        x->start = aux;
        x->start->previous = NULL;
    }
    else if (value >= x->end->value) {
        aux->next = NULL;
        x->end->next = aux;
        aux->previous = x->end;
        x->end = aux;
    }
    else {
        current = x->start;
        while (current->next != NULL && current->next->value < aux->value)
            current = current->next;
        aux->next = current ->next;
        if (current->next != NULL)
            aux->next->previous = aux;
        current->next = aux;
        aux->previous = current;
    }
}

void readList(dlist *x) {
    initList(x);
    int value, x1, x2;
    scanf("%d", &value);
    pushSorted(x, value);
    x1 = value;
    scanf("%d", &value);
    pushSorted(x, value);
    x2 = value;
    do {
        x1 = x2;
        x2 = value;
        scanf("%d", &value);
        pushSorted(x, value);
    } while (value != (x1 + x2) / 2);
}

void printList(dlist x) {
    for (node *i = x.start; i != NULL; i = i->next)
        printf("%d ", i->value);
    printf("\n");
}

int main() {
    dlist x;
    readList(&x);
    printList(x);
}