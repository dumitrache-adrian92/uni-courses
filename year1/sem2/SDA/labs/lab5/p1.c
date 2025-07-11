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

int estePlina(struct Stiva *stiva) {
    return stiva->sus == stiva->capacitate - 1;
}

int esteGoala(struct Stiva *stiva) {
    return stiva->sus == -1;
}

void push(struct Stiva *stiva, int element) {
    if (estePlina(stiva))
        return;
    stiva->tablou[++stiva->sus] = element;
    // printf("%d adaugat in stiva\n", element);
}

int pop(struct Stiva *stiva) {
    if (esteGoala(stiva))
        return INT_MIN;
    return stiva->tablou[stiva->sus--];
}

int peek(struct Stiva *stiva) {
    if (esteGoala(stiva))
        return INT_MIN;
    return stiva->tablou[stiva->sus];
}

int main() {
    struct Stiva *padure = creazaStiva(10);
    padure->capacitate = 6;
    push(padure, 10);
    push(padure, 10);
    push(padure, 10);
    push(padure, 10);
    push(padure, 20);
    push(padure, 10);
    int i, j, val, nr = 0;
    scanf("%d", &i);
    for (j = 0; j < padure->capacitate - i; i++)
        pop(padure);
    val = peek(padure);
    pop(padure);
    while (padure->sus != -1) {
        if (padure->tablou[padure->sus] < val)
            nr++;
        pop(padure);
    }
    printf("%d\n", nr);
}
