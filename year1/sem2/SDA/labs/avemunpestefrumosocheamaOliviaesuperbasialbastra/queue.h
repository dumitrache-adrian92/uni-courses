#ifndef STDLIB_H
    #include <stdlib.h>
#endif

#ifndef QUEUE_H
    typedef struct {
        int front;
        int limit;
        int n;
        char *array;
    } queue;
    void initQueue(queue *x, int maxSize);
    int queueIsEmpty(queue x);
    void pushQueue(queue *x, char val);
    char popQueue(queue *x);
    void freeQueue(queue *x);
#endif