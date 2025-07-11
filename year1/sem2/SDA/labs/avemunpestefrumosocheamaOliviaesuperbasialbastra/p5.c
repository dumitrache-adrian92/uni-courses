#include "queue.h"
#include <stdio.h>
#include <string.h>

void initQueue(queue *x, int maxSize) {
    x->limit = maxSize;
    x->array = malloc(maxSize * sizeof(char));
    x->front = 0;
    x->n = 0;
}

int queueIsEmpty(queue x) {
    return x.n <= 0;
}

void pushQueue(queue *x, char val) {
    int index;
    if (x->n >= x->limit)
        exit(1);
    index = (x->front + x->n) % x->limit;
    x->array[index] = val;
    x->n++;
}

char popQueue(queue *x) {
    char old, vocale[10] = "aeiouAEIOU";
    old = x->array[x->front];
    x->front++;
    x->front %= x->limit;
    x->n--;
    if (strchr(vocale, old))
        return old + 1;
    return old;
}

void freeQueue(queue *x) {
    free(x->array);
}

int main() {
    queue q;
    initQueue(&q, 100);
    pushQueue(&q, 'a');
    pushQueue(&q, 'b');
    pushQueue(&q, 'c');
    pushQueue(&q, 'd');
    pushQueue(&q, 'e');
    printf("%c ", popQueue(&q));
    printf("%c ", popQueue(&q));
    printf("%c ", popQueue(&q));
    printf("%c ", popQueue(&q));
    printf("%c ", popQueue(&q));
    printf("\n");
}