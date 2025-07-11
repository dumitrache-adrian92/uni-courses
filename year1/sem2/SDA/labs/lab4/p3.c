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


void readList(dlist *x, int n, int val) {
    initList(x);
    for (int i = 1; i <= n; i++)
        pushTail(x, i * val);
}


int main() {
    dlist *x;
    int n, val;
    scanf("%d", &n);
    x = malloc(n*sizeof(dlist));
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        readList(&x[i], n, val);
    }
    for (int i = 0; i < n; i++)
        printf("%d ", x[i].end->value);
    printf("\n");
}