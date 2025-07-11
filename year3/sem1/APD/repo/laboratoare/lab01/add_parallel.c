#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

/*
    schelet pentru exercitiul 5
*/

int *arr;
int array_size;
int num_threads;

void *f(void *arg) {
  long id = *(long *)arg;
  int start = id * (double)array_size / num_threads;
  int end = min((id + 1) * (double)array_size / num_threads, array_size);

  for (int i = start; i < end; i++)
    arr[i] += 100;

  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Specificati dimensiunea array-ului si numarul de thread-uri\n");
    exit(-1);
  }

  array_size = atoi(argv[1]);
  num_threads = atoi(argv[2]);

  arr = malloc(array_size * sizeof(int));
  for (int i = 0; i < array_size; i++) {
    arr[i] = i;
  }

  for (int i = 0; i < array_size; i++) {
    printf("%d", arr[i]);
    if (i != array_size - 1) {
      printf(" ");
    } else {
      printf("\n");
    }
  }

  pthread_t threads[num_threads];
  int r;
  long id;
  void *status;
  long ids[num_threads];


  struct timespec start, finish;
  double elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

  // TODO: aceasta operatie va fi paralelizata cu num_threads fire de executie
  for (id = 0; id < num_threads; id++) {
    ids[id] = id;

    r = pthread_create(&threads[id], NULL, f, &ids[id]);

    if (r) {
      printf("Eroare la crearea thread-ului %ld\n", id);
      exit(-1);
    }
  }

  clock_gettime(CLOCK_MONOTONIC, &finish);
  elapsed = (finish.tv_sec - start.tv_sec);
  elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

  for (id = 0; id < num_threads; id++) {
    r = pthread_join(threads[id], &status);

    if (r) {
      printf("Eroare la asteptarea thread-ului %ld\n", id);
      exit(-1);
    }
  }

  for (int i = 0; i < array_size; i++) {
    printf("%d", arr[i]);
    if (i != array_size - 1) {
      printf(" ");
    } else {
      printf("\n");
    }
  }

  printf("%f\n", elapsed);

  return 0;
}
