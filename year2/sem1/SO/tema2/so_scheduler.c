#include "so_scheduler.h"
#include "so_util.h"

static struct so_scheduler *scheduler;

// adds a new element to the priority queue
int enqueue(struct so_thread *new) {
    if (!scheduler)
        return -1;
    if (!new)
        return -1;

    struct so_thread *current = scheduler->first;

    if (scheduler->first == NULL) // first element added
        scheduler->first = new;
    else if (scheduler->first->priority <= new->priority) {
        // add it to the first position
        new->next = scheduler->first;
        scheduler->first->prev = new;
        scheduler->first = new;
    } else {
        // find its position
        struct so_thread *previous = scheduler->first;
        while (current != NULL && current->priority > new->priority) {
            previous = current;
            current = current->next;
        }

        if (current == NULL) {
            // add it at the end of the queue
            previous->next = new;
            new->prev = previous;
        } else {
            // add it in its correct position
            current->prev->next = new;
            new->next = current->prev;
            new->prev = current->prev->next;
            current->prev = new;
        }
    }

    return 0;
}

// returns the next node that should be run if the current thread is preempted
struct so_thread *up_next() {
    struct so_thread *current = scheduler->first;

    while (current != NULL && current->current_state != ready) {
        current = current->next;
    }

    return current;
}

// removes node from queue
static void remove_node(struct so_thread *rm) {
    if (rm->prev == NULL && rm->next == NULL)
        scheduler->first = NULL;
    else if (rm->prev == NULL) {
        rm->next->prev = NULL;
        scheduler->first = rm->next;
    } else if (rm->next == NULL)
        rm->prev->next = NULL;
    else {
        rm->prev->next = rm->next;
        rm->next->prev = rm->prev;
    }
}

// frees all thread structures
static void free_list(struct so_thread *node) {
    for (int i = 0; i < scheduler->thread_count; i++) {
        if (sem_destroy(&scheduler->threads[i]->lock) < 0) {
            perror("sem_destroy");
            exit(EXIT_FAILURE);
        }
        free(scheduler->threads[i]);
    }
}

// runs given thread
void run_next(struct so_thread *next) {
    if (scheduler->current_thread && scheduler->current_thread->current_state != terminated && scheduler->current_thread->current_state != waiting) {
        scheduler->current_thread->current_state = ready;
        enqueue(scheduler->current_thread);
    }
    scheduler->current_thread = next;

    next->current_state = running;
    next->time_left = scheduler->time_quantum;
    remove_node(next);

    if (sem_post(&next->lock) < 0) {
        perror("sem_post");
        exit(EXIT_FAILURE);
    }
}

// figures out which thread should run now
void reschedule() {
    struct so_thread *current = scheduler->current_thread;

    if (current && !up_next()) {
        current->time_left--;
        if (current->time_left <= 0)
            current->time_left = scheduler->time_quantum;

        if (sem_post(&current->lock) < 0) {
            perror("sem_post");
            exit(EXIT_FAILURE);
        }
    } else {
        struct so_thread *next = up_next();
        if (current->current_state == terminated || current->current_state == waiting) {
            run_next(next);
        } else if (next->priority > current->priority) {
            run_next(next);
        } else if (current->time_left <= 0) {
            if (current->priority >= next->priority) {
                run_next(next);
            } else {
                if (sem_post(&current->lock) < 0) {
                    perror("sem_psot");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}

// initializes scheduler structure
int so_init(unsigned int time_quantum, unsigned int io) {
    /* fails if the scheduler has already been initialized */
    if (scheduler)
        return -1;

    /* fails if too many io events are given */
    if (io > SO_MAX_NUM_EVENTS)
        return -1;

    /* fails if a null quantum is given */
    if (time_quantum == 0)
        return -1;

    scheduler = malloc(sizeof(struct so_scheduler));
    if (!scheduler) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    scheduler->time_quantum = time_quantum;
    scheduler->io = io;
    scheduler->current_thread = NULL;
    scheduler->first = NULL;
    scheduler->thread_cap = 100;
    scheduler->thread_count = 0;
    scheduler->threads = malloc(scheduler->thread_cap * sizeof(struct so_thread *));

    if (!scheduler->threads) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    return 0;
}

// waits for all threads to end and frees all structures
void so_end() {
    if (scheduler == NULL)
        return;

    for (int i = 0; i < scheduler->thread_count; i++) {
        if (pthread_join(scheduler->threads[i]->thread, NULL) < 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    free_list(scheduler->first);
    free(scheduler->threads);
    free(scheduler);
    scheduler = NULL;
}

// does nothing and reschedules
void so_exec() {
    struct so_thread *old;
    if (scheduler->current_thread == NULL && up_next() != NULL) {
        if (sem_post(&up_next()->lock) < 0) {
            perror("sem_post");
            exit(EXIT_FAILURE);
        }
    } else if (scheduler->current_thread == NULL && up_next() == NULL) {
        return;
    } else if (up_next() == NULL) {
        return;
    } else {
        old = scheduler->current_thread;
        reschedule();
        if (sem_wait(&old->lock) < 0) {
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }
    }
}

// function used by all new threads to block themselves and run their handler
static void *start_thread(void *arg) {
    struct so_thread *this_thread = arg;

    if (sem_wait(&this_thread->lock)) {
        perror("sem_wait");
        exit(EXIT_FAILURE);
    }

    this_thread->current_state = running;
    this_thread->func(this_thread->priority);

    this_thread->current_state = terminated;

    return NULL;
}

// creates a new thread
tid_t so_fork(so_handler *func, unsigned int priority) {
    // error checking
    if (priority > SO_MAX_PRIO)
        return INVALID_TID;

    if (func == NULL)
        return INVALID_TID;

    // thread creation
    struct so_thread *new_thread = malloc(sizeof(struct so_thread));

    new_thread->current_state = created;
    new_thread->time_left = scheduler->time_quantum;
    new_thread->priority = priority;
    new_thread->io_waiting = -1;
    new_thread->func = func;
    new_thread->next = NULL;
    new_thread->prev = NULL;
    if (sem_init(&new_thread->lock, 0, 0) < 0) {
        perror("sem_init");
        exit(EXIT_FAILURE);
    }
    enqueue(new_thread);

    if (scheduler->thread_count == scheduler->thread_cap) {
        scheduler->thread_cap *= 2;
        scheduler->threads = realloc(scheduler->threads, scheduler->thread_cap * sizeof(struct so_thread *));
        if (!scheduler->threads) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
    }
    scheduler->threads[scheduler->thread_count++] = new_thread;
    new_thread->current_state = ready;

    // starts it and instantly makes it wait
    if (pthread_create(&new_thread->thread, NULL, &start_thread, (void *)new_thread)) {
        perror("pthread_create");
        exit(1);
    }

    // reschedule
    struct so_thread *old;
    if (scheduler->current_thread == NULL) {
        if (sem_post(&new_thread->lock) < 0) {
            perror("sem_post");
            exit(EXIT_FAILURE);
        }
    } else {
        old = scheduler->current_thread;
        reschedule();
        if (sem_wait(&old->lock) < 0) {
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }
    }

    return new_thread->thread;
}

// not finished
int so_wait(unsigned int io) {
    if (io > scheduler->io - 1)
        return -1;

    if (scheduler->current_thread) {
        scheduler->current_thread->current_state = waiting;
        scheduler->current_thread->io_waiting = io;

        struct so_thread *old = scheduler->current_thread;

        reschedule();
        if (sem_wait(&old->lock) < 0) {
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

// not finished
int so_signal(unsigned int io) {
    if (io > scheduler->io - 1)
        return -1;

    return 0;
}