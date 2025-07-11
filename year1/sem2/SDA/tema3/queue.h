#ifndef STDLIB_H
    #include <stdlib.h>
#endif

#ifndef QUEUE_H
    typedef struct {
        int front;
        int limit;
        int n;
        int *array;
    } queue;
    void initQueue(queue *x, int maxSize);
    int queueIsEmpty(queue x);
    void pushQueue(queue *x, int val);
    int popQueue(queue *x);
    void freeQueue(queue *x);
#endif