#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define INSIDE -1 // daca numarul cautat este in interiorul intervalului
#define OUTSIDE -2 // daca numarul cautat este in afara intervalului

struct my_arg {
	int id;
	int N;
	int P;
	int number;
	int *left;
	int *right;
	int *keep_running;
	int *v;
	int *found;
};

pthread_barrier_t barrier;
pthread_mutex_t mutex;

int min(int a, int b) {
	return a < b ? a : b;
}

/*
void binary_search() {
	while (keep_running) {
		int mid = left + (right - left) / 2;
		if (left > right) {
			printf("Number not found\n");
			break;
		}

		if (v[mid] == number) {
			keep_running = 0;
			printf("Number found at position %d\n", mid);
		} else if (v[mid] > number) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
}
*/

void *f(void *arg)
{
	struct my_arg* data = (struct my_arg*) arg;

	while (*data->keep_running) {
		pthread_barrier_wait(&barrier);
		int N = *data->right - *data->left;
		int thread_id = data->id;
		int P = data->P;
		int start = *data->left + thread_id * (double)N / P;
		int end = *data->left + min((thread_id + 1) * (double)N / P, N);

		if (data->v[start] == data->number) { // found
			*data->keep_running = 0;
			*data->found = start;
		} else if (data->v[end - 1] == data->number) { // found
			*data->keep_running = 0;
			*data->found = end - 1;
		} else if (data->v[start] < data->number && data->v[end - 1] > data->number) { // is in this interval
			*data->left = start + 1;
			*data->right = end - 1;
		} else if (data->v[*data->left] > data->number || data->v[*data->right - 1] < data->number) { // can't exist in any interval
			if (thread_id == 0)
				*data->keep_running = 0;
		}

		pthread_barrier_wait(&barrier);
	}

	return NULL;
}

void display_vector(int *v, int size) {
	int i;

	for (i = 0; i < size; i++) {
		printf("%d ", v[i]);
	}

	printf("\n");
}


int main(int argc, char *argv[])
{
	int r, N, P, number, keep_running, left, right;
	int *v;
	int *found;
	void *status;
	pthread_t *threads;
	struct my_arg *arguments;

	if (argc < 4) {
		printf("Usage:\n\t./ex N P number\n");
		return 1;
	}

	N = atoi(argv[1]);
	P = atoi(argv[2]);
	number = atoi(argv[3]);

	keep_running = 1;
	left = 0;
	right = N;

	v = (int*) malloc(N * sizeof(int));
	threads = (pthread_t*) malloc(P * sizeof(pthread_t));
	arguments = (struct my_arg*) malloc(P * sizeof(struct my_arg));
	found = (int*) malloc(P * sizeof(int));
	*found = -1;

	for (int i = 0; i < N; i++) {
		v[i] = i * 2;
	}

	display_vector(v, N);

	pthread_barrier_init(&barrier, NULL, P);
	pthread_mutex_init(&mutex, NULL);

	for (int i = 0; i < P; i++) {
		arguments[i].id = i;
		arguments[i].N = N;
		arguments[i].P = P;
		arguments[i].number = number;
		arguments[i].left = &left;
		arguments[i].right = &right;
		arguments[i].keep_running = &keep_running;
		arguments[i].v = v;
		arguments[i].found = found;

		r = pthread_create(&threads[i], NULL, f, &arguments[i]);

		if (r) {
			printf("Eroare la crearea thread-ului %d\n", i);
			exit(-1);
		}
	}

	for (int i = 0; i < P; i++) {
		r = pthread_join(threads[i], &status);

		if (r) {
			printf("Eroare la asteptarea thread-ului %d\n", i);
			exit(-1);
		}
	}

	if (*found != -1) {
		printf("Number found at position %d\n", *found);
	} else {
		printf("Number not found\n");
	}

	free(v);
	free(threads);
	free(arguments);
	free(found);
	pthread_barrier_destroy(&barrier);
	pthread_mutex_destroy(&mutex);

	return 0;
}
