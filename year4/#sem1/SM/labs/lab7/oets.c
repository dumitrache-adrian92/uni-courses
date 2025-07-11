#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

pthread_barrier_t barrier;

typedef struct oets_arg {
    int id;
    int *v;
    int N;
    int P;
    int *sorted;
} oets_arg;

int min(int a, int b) {
	return a < b ? a : b;
}

void display_vector(int *v, int N) {
	int i;

	for (i = 0; i < N; i++) {
		printf("%i ", v[i]);
	}

	printf("\n");
}

void *thread_function(void *arg)
{
	int ID = ((oets_arg *) arg)->id;
    int *v = ((oets_arg *) arg)->v;
    int N = ((oets_arg *) arg)->N;
    int P = ((oets_arg *) arg)->P;
    int *sorted = ((oets_arg *) arg)->sorted;

	int start = ID * (double) N / P;
	int end = min((ID + 1) * (double) N / P, N);

	int startEven = start % 2 == 0 ? start : start + 1;
	int endEven = end % 2 == 0 ? end : end + 1;
	endEven = min(endEven, N - 1);

	int startOdd = start % 2 == 0 ? start + 1 : start;
	int endOdd = end % 2 == 0 ? end + 1 : end;
	endOdd = min(endOdd, N - 1);

	int srt;
	while (!*sorted) {
		pthread_barrier_wait(&barrier);

		srt = 1;
		*sorted = 1;
		for (int i = startEven; i < endEven; i += 2) {
			if (v[i] < v[i + 1]) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				srt = 0;
			}
		}

		pthread_barrier_wait(&barrier);

		for (int i = startOdd; i < endOdd; i += 2) {
			if (v[i] < v[i + 1]) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				srt = 0;
			}
		}

		if (!srt) {
			*sorted = 0;
        }

		pthread_barrier_wait(&barrier);
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
        printf("Usage: %s <arr_len> <num_threads>\n", argv[0]);
        exit(1);
    }

    int N;
    int P;

    N = atoi(argv[1]);
	P = atoi(argv[2]);

    int *v;

	v = (int *) malloc(sizeof(int) * N);

	if (v == NULL) {
		perror("malloc");
		exit(1);
	}

	srand(42);

	for (int i = 0; i < N; i++) {
		v[i] = rand() % N;
    }

	int i;
	pthread_t tid[P];
	oets_arg thread_arg[P];
    int sorted = 0;


	void *ret;


	pthread_barrier_init(&barrier, NULL, P);
	for (i = 0; i < P; i++) {
		thread_arg[i].id = i;
        thread_arg[i].v = v;
        thread_arg[i].N = N;
        thread_arg[i].P = P;
        thread_arg[i].sorted = &sorted;

		pthread_create(&tid[i], NULL, thread_function, &thread_arg[i]);
	}

	for (i = 0; i < P; i++) {
		pthread_join(tid[i], &ret);
	}

	display_vector(v, N);

	free(v);

	return 0;
}
