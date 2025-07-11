#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

int N;
int P;
int threads_running;
int *time_to_wait;
sem_t semaphore;

void get_args(int argc, char **argv)
{
    P = atoi(argv[1]);
    time_to_wait = malloc(sizeof(int) * P);
    threads_running = P - 1;

    for (int i = 1; i < P; i++) {
        time_to_wait[i] = atoi(argv[i + 1]);
    }
}

void *thread_function(void *arg)
{
	int thread_id = *(int *)arg;

    if (thread_id == 0) {
        while (threads_running) {
            sem_wait(&semaphore);

            for (int i = 1; i < P; i++) {
                if (time_to_wait[i] == 0) {
                    printf("Thread-ul %d s-a terminat\n", i);
                    time_to_wait[i] = -1;
                    threads_running--;
                    break;
                }
            }
        }
    } else {
        sleep(time_to_wait[thread_id]);

        time_to_wait[thread_id] = 0;
        sem_post(&semaphore);
    }

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	get_args(argc, argv);

	int i;
	int thread_id[P];
	pthread_t tid[P];

    sem_init(&semaphore, 0, 0);

	// se creeaza thread-urile
	for (i = 0; i < P; i++) {
		thread_id[i] = i;
		pthread_create(&tid[i], NULL, thread_function, &thread_id[i]);
	}

	// se asteapta thread-urile
	for (i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	free(time_to_wait);
	return 0;
}
