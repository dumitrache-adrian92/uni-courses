#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int N;
int P;
int X;
int *v;
int *thread_count;
int *thread_index_sum;
pthread_barrier_t barrier;

void get_args(int argc, char **argv)
{
	if(argc < 4) {
		printf("Numar insuficient de parametri: %s N P X\n", argv[0]);
		exit(1);
	}

	N = atoi(argv[1]);
	P = atoi(argv[2]);
    X = atoi(argv[3]);
}

void init()
{
	int i;
	v = malloc(sizeof(int) * N);
    thread_count = calloc(P, sizeof(int));
    thread_index_sum = calloc(P, sizeof(int));

	if (v == NULL || thread_count == NULL || thread_index_sum == NULL) {
		printf("Eroare la malloc/calloc!");
		exit(1);
	}

	for (i = 0; i < N; i++) {
		v[i] = (i + 3) % 5;
    }
}

void *thread_function(void *arg)
{
	int thread_id = *(int *)arg;
	int start = thread_id * (double)N / P;
	int end = fmin((thread_id + 1) * (double)N / P, N);

    for (int i = start; i < end; i++) {
        if (v[i] == X) {
            thread_count[thread_id]++;
            thread_index_sum[thread_id] += i;
        }
    }

    pthread_barrier_wait(&barrier);

    if (thread_id == 0) {
        int count = 0;
        int index_sum = 0;

        for (int i = 0; i < P; i++) {
            count += thread_count[i];
            index_sum += thread_index_sum[i];
        }

        printf("%d %d\n", count, index_sum);
    }

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	get_args(argc, argv);
	init();

	int i;
	int thread_id[P];
	pthread_t tid[P];

	pthread_barrier_init(&barrier, NULL, P);
	// se creeaza thread-urile
	for (i = 0; i < P; i++) {
		thread_id[i] = i;
		pthread_create(&tid[i], NULL, thread_function, &thread_id[i]);
	}

	// se asteapta thread-urile
	for (i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	free(v);
    free(thread_count);
    free(thread_index_sum);
	return 0;
}
