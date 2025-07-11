#include "dlist.h"

int emptyList(dlist x) {
    if (!x.start)
        return 1;
    return 0;
}

void initList(dlist *x) {
    x->start = x->end = NULL;
}

void pushTail(dlist *x, unsigned int timestamp, double value) {
    node *aux = (node *)malloc(sizeof(node));
    aux->value = value;
    aux->timestamp = timestamp;
    aux->toRemove = 0;
    aux->previous = x->end;
    aux->next = NULL;
    x->end = aux;
    if (emptyList(*x))
        x->start = aux;
    else
        aux->previous->next = aux;
}

void readList(dlist *x) {
    initList(x);
    scanf("%u", &(x->n));
    double value;
    int timestamp;
    for (int i = 0; i < x->n; i++) {
        scanf("%d", &timestamp);
        scanf("%lf", &value);
        pushTail(x, timestamp, value);
    }
}

void printList(dlist x) {
    printf("%d\n", x.n);
    for (node *i = x.start; i != NULL; i = i->next)
        printf("%d %0.2f\n", i->timestamp, i->value);
}

void freeList(dlist *x) {
    node *i = x->start;
    void *rm;
    while (i != NULL) {
        rm = i;
        i = i->next;
        free(rm);
    }
    x->start = NULL;
    x->end = NULL;
    x->n = 0;
}

double windowMean(node *x, int k) {
    double sum = x->value;
    node *y = x;
    for (int i = 0; i < k / 2; i++) {
        x = x->next;
        y = y->previous;
        sum += x->value + y->value;
    }
    return sum / k;
}

double standardDeviation(node *x, int k) {
    node *y = x;
    double median = windowMean(x, k);
    double sum = pow(x->value - median, 2);
    for (int i = 0; i < k / 2; i++) {
        x = x->next;
        y = y->previous;
        sum += pow(x->value - median, 2) +
               pow(y->value - median, 2);
    }
    return sqrt(sum / k);
}

void removeExceptions(dlist *x, int k) {
    int i;
    node *current = x->start, *lastToVerify = x->end;
    for (i = 0; i < k / 2; i++) {
        current = current->next;
        lastToVerify = lastToVerify->previous;
    }
    double median, deviation;
    while (current != lastToVerify->next) {
        median = windowMean(current, k);
        deviation = standardDeviation(current, k);
        if (current->value > median + deviation ||
            current->value < median - deviation)
            current->toRemove = 1;
        current = current->next;
    }
    current = x->start;
    while (current != NULL)
        if (current->toRemove == 1) {
            if (current->next == NULL) {
                removeNode(x, current);
                break;
            }
            current = current->next;
            removeNode(x, current->previous);
        } else
            current = current->next;
}

void removeNode(dlist *x, node *rm) {
    if (x->start == rm)
        x->start = rm->next;
    if (rm->next != NULL)
        rm->next->previous = rm->previous;
    if (rm->previous != NULL)
        rm->previous->next = rm->next;
    x->n--;
    free(rm);
}

void medianNode(dlist *list, node *x, int k) {
    node *current = x, *current2;
    int pos, midTimestamp;
    for (int i = 0; i < k / 2; i++)
        current = current->next;
    midTimestamp = current->timestamp;
    current = x;
    for (int i = 0; i < k; i++) {
        pos = 1;
        current2 = x;
        for (int j = 0; j < k; j++) {
            if (current2->value < current->value)
                pos++;
            current2 = current2->next;
        }
        if (pos == k / 2 + 1) {
            pushTail(list, midTimestamp, current->value);
            list->n++;
            break;
        }
        current = current->next;
    }
}

void medianFilter(dlist *x, int k) {
    node *last = x->end, *current, *oldEnd = x->end;
    int i;
    for (i = 0; i < k - 1; i++)
        last = last->previous;
    for (current = x->start; current != last->next; current = current->next)
        medianNode(x, current, k);
    current = x->start;
    oldEnd = oldEnd->next;
    void *rm;
    while (current != oldEnd) {
        rm = current;
        current = current->next;
        removeNode(x, rm);
    }
}

void meanFilter(dlist *x, int k) {
    int i;
    node *oldEnd = x->end;
    node *current = x->start, *lastToVerify = x->end;
    for (i = 0; i < k / 2; i++) {
        current = current->next;
        lastToVerify = lastToVerify->previous;
    }
    while (current != lastToVerify->next) {
        pushTail(x, current->timestamp, windowMean(current, k));
        x->n++;
        current = current->next;
    }
    current = x->start;
    oldEnd = oldEnd->next;
    void *rm;
    while (current != oldEnd) {
        rm = current;
        current = current->next;
        removeNode(x, rm);
    }
}

void equalize(dlist *x) {
    double currentTimestamp, previousTimestamp;
    for (node *current = x->start->next; current != NULL; current = current->next) {
        previousTimestamp = current->previous->timestamp / 1000.0;
        currentTimestamp = current->timestamp / 1000.0;
        if (currentTimestamp - previousTimestamp >= 0.1 &&
            currentTimestamp - previousTimestamp <= 1) {
            current->value = (current->value + current->previous->value) / 2.0;
            current->timestamp = (current->timestamp + current->previous->timestamp) / 2;
        }
    }
}

int stringToInt(char *str) {
    int value = 0;
    for (int i = 0; str[i] != '\0'; i++)
        value = value * 10 + (str[i] - '0');
    return value;
}

void statistics(dlist *x, int delta) {
    double min, max;
    int lowerBound, upperBound, i, frequency;
    min = max = x->start->value;
    for (node *current = x->start->next; current != NULL; current = current->next) {
        if (min > current->value)
            min = current->value;
        if (max < current->value)
            max = current->value;
    }
    lowerBound = 0;
    if (min < 0)
        while (lowerBound > min)
            lowerBound -= delta;
    else {
        while (lowerBound < min)
            lowerBound += delta;
    }
    upperBound = 0;
    if (max < 0) {
        while (upperBound > max)
            upperBound -= delta;
        upperBound += delta;
    } else
        while (upperBound < max)
            upperBound += delta;
    for (i = lowerBound; i < upperBound; i += delta) {
        frequency = 0;
        for (node *current = x->start; current != NULL; current = current->next)
            if (current->value >= i && current->value <= i + delta)
                frequency++;
        if (frequency != 0)
            printf("[%d, %d] %d\n", i, i + delta, frequency);
    }
}

double wCalc(int i, int k) {
    double sum = 0;
    for (int j = 0; j < k; j++)
        sum += pow((double)j / (k - 1), 2) * 0.9 + 0.1;
    return (pow((double)i / (k - 1), 2) * 0.9 + 0.1) / sum;
}

void pushAfterNode(node *x, int timestamp, double value) {
    node *aux = (node *)malloc(sizeof(node));
    aux->value = value;
    aux->timestamp = timestamp;
    aux->toRemove = 0;
    aux->previous = x;
    aux->next = x->next;
    x->next = aux;
    aux->next->previous = aux;
}

void dataCompletion(dlist *x, int k) {
    node *current = x->start, *lastToVerify = x->end, *left, *right, *lastAdded;
    double C, w, a, b;
    int newTimestamp, i, nextTimestamp;
    for (i = 0; i < k - 1; i++) {
        current = current->next;
        lastToVerify = lastToVerify->previous;
    }
    while (current != lastToVerify) {
        if (current->next->timestamp - current->timestamp > 1000.00) {
            newTimestamp = current->timestamp + 200;
            lastAdded = current;
            nextTimestamp = current->next->timestamp;
            while (newTimestamp < nextTimestamp) {
                left = current;
                right = lastAdded->next;
                a = b = 0;
                C = ((double)newTimestamp - left->timestamp) /
                    ((double)right->timestamp - left->timestamp);
                for (i = k - 1; i >= 0; i--) {
                    w = wCalc(i, k);
                    a += left->value * w;
                    b += right->value * w;
                    left = left->previous;
                    right = right->next;
                }
                a = (1 - C) * a + C * b;
                pushAfterNode(lastAdded, newTimestamp, a);
                x->n++;
                lastAdded = lastAdded->next;
                newTimestamp += 200;
            }
            current = lastAdded;
        }
        current = current->next;
    }
}