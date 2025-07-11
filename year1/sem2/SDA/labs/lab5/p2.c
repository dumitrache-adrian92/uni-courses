#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int front, rear, size;
    unsigned capacity;
    char *array;
};

struct Queue *createQueue(unsigned capacity) {
    struct Queue *queue = (struct Queue *)malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (char *)malloc(
        queue->capacity * sizeof(char));
    return queue;
}

int isFull(struct Queue *queue) {
    return (queue->size == queue->capacity);
}

int isEmpty(struct Queue *queue) {
    return (queue->size == 0);
}

void enqueue(struct Queue *queue, char item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    printf("%c enqueued to queue\n", item);
}

int dequeue(struct Queue *queue) {
    if (isEmpty(queue))
        return INT_MIN;
    char item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

int front(struct Queue *queue) {
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}

int rear(struct Queue *queue) {
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}

int main() {
    struct Queue *operators = createQueue(1000);
    struct Queue *numbas = createQueue(1000);
    int val, multiply, result = 0;
    enqueue(numbas, '1');
    enqueue(operators, '+');
    enqueue(numbas, '3');
    while (!isEmpty(numbas)) {
        val = front(numbas) - '0';
        dequeue(numbas);
        if (front(operators) == '+')
            result += val + (front(numbas) - '0');
        else if (front(operators) == '-')
            result += val - (front(numbas) - '0');
        else if (front(operators) == '*')
            result += val - (front(numbas) - '0');
        dequeue(operators);
        dequeue(numbas);
    }
    printf("%d", result);
    return 0;
}