#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int value;
    struct Node *previous;
    struct Node *next;
} node;

typedef struct {
    int n;
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
    aux->next = x->start;
    x->end = aux;
    if (emptyList(*x)) {
        x->start = aux;
    }
    else
        aux->previous->next = aux;
}


void readList(dlist *x) {
    initList(x);
    int value;
    scanf("%d", &x->n);
    for (int i = 0; i < x->n ;i++) {
        scanf("%d", &value);
        pushTail(x, value);
    }
}

void printList(dlist x) {
    int k;
    node *current = x.start, *current2;
    for (int i = 0; i < x.n; i++) {
        current2= current;
        for (int j = 0; j < x.n; j++) {
            printf("%d ", current2->value);
            current2= current2->next;
        }
        current = current -> next;
            printf("\n");
    }
}

int main() {
    dlist x;
    readList(&x);
    printList(x);
}