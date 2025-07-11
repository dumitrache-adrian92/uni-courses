#include "queue.h"

void initQueue(queue *x, int maxSize) {
    x->limit = maxSize;
    x->array = malloc(maxSize * sizeof(int));
    x->front = 0;
    x->n = 0;
}

int queueIsEmpty(queue x) {
    return x.n <= 0;
}

void pushQueue(queue *x, int val) {
    int index;
    if (x->n >= x->limit)
        exit(1);
    index = (x->front + x->n) % x->limit;
    x->array[index] = val;
    x->n++;
}

int popQueue(queue *x) {
    int old;
    old = x->array[x->front];
    x->front++;
    x->front %= x->limit;
    x->n--;
    return old;
}

void freeQueue(queue *x) {
    free(x->array);
}
