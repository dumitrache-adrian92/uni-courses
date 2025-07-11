#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct Stiva {
    int sus;
    unsigned capacitate;
    int *tablou;
};

struct Stiva *creazaStiva(unsigned capacitate) {
    struct Stiva *stiva = (struct Stiva *)malloc(sizeof(struct Stiva));
    stiva->capacitate = capacitate;
    stiva->sus = -1;
    stiva->tablou = (int *)malloc(stiva->capacitate * sizeof(int));
    return stiva;
}
int esteGoala(struct Stiva *stiva) {
    return stiva->sus == -1;
}

void push(struct Stiva *stiva, int element) {
    if (estePlina(stiva))
        return;
    stiva->tablou[++stiva->sus] = element;
    printf("%d adaugat in stiva\n", element);
}

int pop(struct Stiva *stiva) {
    if (esteGoala(stiva))
        return INT_MIN;
    return stiva->tablou[stiva->sus--];
}

struct Coada {
    struct Stiva *s1, *s2;
};

void add(struct Coada *queue, int x){
    while(!esteGoala(queue->s1)) {
        push(queue->s2, queue->s1->tablou[queue->s1->sus]);
        pop(queue->s1);
    }
    push(queue->s1, x);
    while(!esteGoala(queue->s2)) {
        push(queue->s1, queue->s2->tablou[queue->s2->sus]);
        pop(queue->s2);
    }
}

void remove(struct Coada *queue) {
    if (esteGoala(queue->s1)) {
        printf("e deja goala");
    }
    pop(queue->s1);
}

int peek(struct Coada *queue) {
    if (esteGoala(queue->s1))
        return INT_MIN;
    return queue->s1->tablou[queue->s1->sus];
}