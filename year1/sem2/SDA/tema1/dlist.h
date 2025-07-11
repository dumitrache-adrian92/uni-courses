#ifndef STDLIB_H
#include <stdlib.h>
#endif

#ifndef STDIO_H
#include <stdio.h>
#endif

#ifndef MATH_H
#include <math.h>
#endif

#ifndef DLIST_H
typedef struct Node {
    unsigned int timestamp;
    double value;
    struct Node *previous;
    struct Node *next;
    int toRemove;
} node;

typedef struct {
    unsigned int n;
    node *start;
    node *end;
} dlist;

void roundList(dlist *x);
int emptyList(dlist x);
void initList(dlist *x);
void readList(dlist *x);
void pushTail(dlist *x, unsigned int timestamp, double value);
void printList(dlist x);
void freeList(dlist *x);
double windowMean(node *x, int k);
double standardDeviation(node *x, int k);
void removeExceptions(dlist *x, int k);
void removeNode(dlist *x, node *rm);
void medianNode(dlist *list, node *x, int k);
void medianFilter(dlist *x, int k);
void meanFilter(dlist *x, int k);
void equalize(dlist *x);
void statistics(dlist *x, int delta);
int stringToInt(char *str);
void dataCompletion(dlist *x, int k);
double wCalc(int i, int k);
void pushAfterNode(node *x, int timestamp, double value);
#endif