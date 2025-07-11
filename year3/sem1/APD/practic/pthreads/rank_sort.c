#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int N;
int P;
int *v;
int *vQSort;
int *vNew;
pthread_barrier_t barrier;

int min(int a, int b) {
	return a < b ? a : b;
}

void display_vector(int *v) {
	for (int i = 0; i < N; i++) {
		printf("%d ", v[i]);
	}

	printf("\n");
}

void get_args(int argc, char **argv)
{
	if(argc < 3) {
		printf("Numar insuficient de parametri: %s N P\n", argv[0]);
		exit(1);
	}

	N = atoi(argv[1]);
	P = atoi(argv[2]);
}

void init()
{
	int i;
	v = malloc(sizeof(int) * N);
	vNew = malloc(sizeof(int) * N);

	if (v == NULL || vNew == NULL) {
		printf("Eroare la malloc!");
		exit(1);
	}

	for (i = 0; i < N; i++)
		v[i] = N - i + 5;
}

void *thread_function(void *arg)
{
	int thread_id = *(int *)arg;
	int start = thread_id * (double)N / P;
	int end = min((thread_id + 1) * (double)N / P, N);

	for (int i = start; i < end; i++) {
        int count = 0;

        for (int j = 0; j < N; j++) {
            if (v[j] < v[i]) {
                count++;
            }
        }

        vNew[count] = v[i];
    }

    pthread_barrier_wait(&barrier);

    if (thread_id == 0)
        display_vector(vNew);

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
	free(vNew);

	return 0;
}
