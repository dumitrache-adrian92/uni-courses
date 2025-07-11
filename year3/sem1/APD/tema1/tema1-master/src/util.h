#ifndef UTIL_H
#define UTIL_H

#include "helpers.h"
#include <pthread.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    int ID; // thread ID
    int P; // number of threads
    int p, q; // p x q grid of samples
    int step_x, step_y;
    unsigned char sigma;
    ppm_image *image; // input image
    ppm_image *scaled_image; // scaled input image
    unsigned char **grid; // grid of samples
    ppm_image **contour_map;
    pthread_barrier_t *scale_barrier; // barrier where threads wait for the entire image to be scaled
} thread_args;

#endif