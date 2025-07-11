#ifndef SO_UTIL_H
#define SO_UTIL_H

#include "so_scheduler.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

enum state { created = 0,
             ready = 1,
             running = 2,
             waiting = 3,
             terminated = 4 };

/* structure that represents a thread along with all its information.
 * also contains a pointer to another thread, which we will use to form a
 * priority queue based on a doubly linked list */
struct so_thread {
    pthread_t thread;
    unsigned int time_left;
    unsigned int priority;
    enum state current_state;
    unsigned int io_waiting;
    so_handler *func;

    sem_t lock;

    struct so_thread *next;
    struct so_thread *prev;
};

struct so_scheduler {
    struct so_thread *current_thread;
    unsigned int time_quantum;
    unsigned int io;
    struct so_thread *first;

    struct so_thread** threads;
    int thread_cap;
    int thread_count;
};
#endif