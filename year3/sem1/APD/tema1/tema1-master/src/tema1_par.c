// Author: APD team, except where source was noted
#include "util.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define CONTOUR_CONFIG_COUNT    16
#define FILENAME_MAX_SIZE       50
#define STEP                    8
#define SIGMA                   200
#define RESCALE_X               2048
#define RESCALE_Y               2048

#define CLAMP (v, min, max) if (v < min) { v = min; } else if (v > max) { v = max; }

unsigned char **alloc_grid(int p, int q) {
    unsigned char **grid = (unsigned char **) calloc((p + 1), sizeof(unsigned char*));
    if (!grid) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    for (int i = 0; i <= p; i++) {
        grid[i] = (unsigned char *) calloc((q + 1), sizeof(unsigned char));
        if (!grid[i]) {
            fprintf(stderr, "Unable to allocate memory\n");
            exit(1);
        }
    }

    return grid;
}

// Allocates memory for the scaled image if necessary, otherwise returns the original image.
ppm_image *alloc_scaled_image(ppm_image *image) {
    ppm_image *scaled_image = NULL;

    // we only rescale downwards
    if (image->x <= RESCALE_X && image->y <= RESCALE_Y) {
        scaled_image = image;
    } else {
        // alloc memory for image
        scaled_image = (ppm_image *) malloc(sizeof(ppm_image));
        if (!scaled_image) {
            fprintf(stderr, "Unable to allocate memory\n");
            exit(1);
        }
        scaled_image->x = RESCALE_X;
        scaled_image->y = RESCALE_Y;

        scaled_image->data = (ppm_pixel*) malloc(scaled_image->x * scaled_image->y * sizeof(ppm_pixel));
        if (!scaled_image) {
            fprintf(stderr, "Unable to allocate memory\n");
            exit(1);
        }
    }

    return scaled_image;
}

// Creates a map between the binary configuration (e.g. 0110_2) and the corresponding pixels
// that need to be set on the output image. An array is used for this map since the keys are
// binary numbers in 0-15. Contour images are located in the './contours' directory.
ppm_image **init_contour_map() {
    ppm_image **map = (ppm_image **) malloc(CONTOUR_CONFIG_COUNT * sizeof(ppm_image *));

    if (!map) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    for (int i = 0; i < CONTOUR_CONFIG_COUNT; i++) {
        char filename[FILENAME_MAX_SIZE];
        sprintf(filename, "./contours/%d.ppm", i);
        map[i] = read_ppm(filename);
    }

    return map;
}

// Updates a particular section of an image with the corresponding contour pixels.
// Used to create the complete contour image.
void update_image(ppm_image *image, ppm_image *contour, int x, int y) {
    for (int i = 0; i < contour->x; i++) {
        for (int j = 0; j < contour->y; j++) {
            int contour_pixel_index = contour->x * i + j;
            int image_pixel_index = (x + i) * image->y + y + j;

            image->data[image_pixel_index].red = contour->data[contour_pixel_index].red;
            image->data[image_pixel_index].green = contour->data[contour_pixel_index].green;
            image->data[image_pixel_index].blue = contour->data[contour_pixel_index].blue;
        }
    }
}

// Rescales the image using bicubic interpolation.
// It will only calculate the lines of pixels between `start` and `end` so each
// thread can work on a different part of the image.
void rescale_image(ppm_image *image, ppm_image *new_image, int start, int end) {
    uint8_t sample[3];

    // use bicubic interpolation for scaling
    for (int i = start; i < end; i++) {
        for (int j = 0; j < new_image->y; j++) {
            float u = (float)i / (float)(new_image->x - 1);
            float v = (float)j / (float)(new_image->y - 1);
            sample_bicubic(image, u, v, sample);

            new_image->data[i * new_image->y + j].red = sample[0];
            new_image->data[i * new_image->y + j].green = sample[1];
            new_image->data[i * new_image->y + j].blue = sample[2];
        }
    }
}

// Corresponds to step 1 of the marching squares algorithm, which focuses on sampling the image.
// Builds a p x q grid of points with values which can be either 0 or 1, depending on how the
// pixel values compare to the `sigma` reference value. The points are taken at equal distances
// in the original image, based on the `step_x` and `step_y` arguments.
// Will only sample the lines of pixels between `start` and `end` so each thread can work on
// a different part of the image.
void sample_grid(ppm_image *image, int step_x, int step_y, unsigned char sigma,
                    unsigned char **grid, int start, int end, int p, int q) {

    // This will generate an extra line of samples that is needed by the march
    // step. Even though this is redundant, it's faster than having threads
    // wait at yet another barrier.
    for (int i = start; i <= end && i < p; i++) {
        for (int j = 0; j < q; j++) {
            ppm_pixel curr_pixel = image->data[i * step_x * image->y + j * step_y];

            unsigned char curr_color = (curr_pixel.red + curr_pixel.green + curr_pixel.blue) / 3;

            if (curr_color > sigma) {
                grid[i][j] = 0;
            } else {
                grid[i][j] = 1;
            }
        }
    }

    // last sample points have no neighbors below / to the right, so we use pixels on the
    // last row / column of the input image for them
    for (int i = start; i <= end && i < p; i++) {
        ppm_pixel curr_pixel = image->data[i * step_x * image->y + image->x - 1];

        unsigned char curr_color = (curr_pixel.red + curr_pixel.green + curr_pixel.blue) / 3;

        if (curr_color > sigma) {
            grid[i][q] = 0;
        } else {
            grid[i][q] = 1;
        }
    }

    if (end == p) {
        for (int j = 0; j < q; j++) {
            ppm_pixel curr_pixel = image->data[(image->x - 1) * image->y + j * step_y];

            unsigned char curr_color = (curr_pixel.red + curr_pixel.green + curr_pixel.blue) / 3;

            if (curr_color > sigma) {
                grid[p][j] = 0;
            } else {
                grid[p][j] = 1;
            }
        }
    }
}

// Corresponds to step 2 of the marching squares algorithm, which focuses on identifying the
// type of contour which corresponds to each subgrid. It determines the binary value of each
// sample fragment of the original image and replaces the pixels in the original image with
// the pixels of the corresponding contour image accordingly.
// Will only march the lines of samples between `start` and `end` so each thread can work on
// a different part of the final contour image.
void march(ppm_image *image, unsigned char **grid, ppm_image **contour_map, int step_x, int step_y, int start, int end, int q) {
    int p = image->x / step_x;
    for (int i = start; i < end; i++) {
        for (int j = 0; j < q; j++) {
            unsigned char k = 8 * grid[i][j] + 4 * grid[i][j + 1] + 2 * grid[i + 1][j + 1] + 1 * grid[i + 1][j];
            update_image(image, contour_map[k], i * step_x, j * step_y);
        }
    }
}

// Calls `free` method on the utilized resources.
void free_resources(ppm_image *image, ppm_image *scaled_image, ppm_image **contour_map, unsigned char **grid, int step_x, pthread_barrier_t *barrier) {
    for (int i = 0; i < CONTOUR_CONFIG_COUNT; i++) {
        free(contour_map[i]->data);
        free(contour_map[i]);
    }
    free(contour_map);

    for (int i = 0; i <= scaled_image->x / step_x; i++) {
        free(grid[i]);
    }
    free(grid);

    free(scaled_image->data);
    free(scaled_image);
    if (scaled_image != image) {
        free(image->data);
        free(image);
    }

    int rc = pthread_barrier_destroy(barrier);

    if (rc != 0) {
        fprintf(stderr, "Error destroying barrier\n");
        exit(1);
    }

    free(barrier);
}

// Thread function which handles the rescaling and marching squares algorithm
// for a part of the image.
void *thread_function(void *arg) {
    thread_args *args = (thread_args *)arg;
    int ID = args->ID;
    int P = args->P;
    int N = args->p;
    ppm_image *image = args->image;
    ppm_image *scaled_image = args->scaled_image;

    if (image != scaled_image) {
        int rescale_start = ID * (double) scaled_image->x / P;
        int rescale_end = min((ID + 1) * (double)scaled_image->x / P, scaled_image->x);
        rescale_image(image, scaled_image, rescale_start, rescale_end);
    }

    int start = ID * (double)N / P;
	int end = min((ID + 1) * (double)N / P, N);

    // The rescaling has to be finished before each thread can run the marching
    // squares algorithm
    int rc = pthread_barrier_wait(args->scale_barrier);

    if (rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD) {
        fprintf(stderr, "Error waiting on barrier\n");
        exit(1);
    }

    sample_grid(scaled_image, args->step_x, args->step_y, args->sigma, args->grid, start, end, args->p, args->q);
    march(scaled_image, args->grid, args->contour_map, args->step_x, args->step_y, start, end, args->q);

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: ./tema1 <in_file> <out_file> <P>\n");
        return 1;
    }

    ppm_image *image = read_ppm(argv[1]);
    int step_x = STEP;
    int step_y = STEP;
    int P = atoi(argv[3]);

    // Compute the maximum number of samples, based on the image size (takes
    // into account whether the image will be rescaled or not)
    int p = min(image->x, RESCALE_X) / step_x;
    int q = min(image->y, RESCALE_Y) / step_y;

    // 0. Initialize contour map
    ppm_image **contour_map = init_contour_map();

    // 1. Allocate memory for grid and for the rescaled image (if needed!)
    unsigned char **grid = alloc_grid(p, q);
    ppm_image *scaled_image = alloc_scaled_image(image);
    pthread_barrier_t *barrier = (pthread_barrier_t *) malloc(sizeof(pthread_barrier_t));
    int rc = pthread_barrier_init(barrier, NULL, P);
    if (rc != 0) {
        fprintf(stderr, "Error initializing barrier\n");
        exit(1);
    }

    // 2. Rescale + Marching squares in parallel
    pthread_t threads[P];
    thread_args *args[P];

    for (int i = 0; i < P; i++) {
        args[i] = (thread_args *) malloc(sizeof(thread_args));
        if (!args[i]) {
            fprintf(stderr, "Unable to allocate memory\n");
            exit(1);
        }

        args[i]->ID = i;
        args[i]->P = P;
        args[i]->p = p;
        args[i]->q = q;
        args[i]->step_x = step_x;
        args[i]->step_y = step_y;
        args[i]->sigma = SIGMA;
        args[i]->image = image;
        args[i]->scaled_image = scaled_image;
        args[i]->grid = grid;
        args[i]->contour_map = contour_map;
        args[i]->scale_barrier = barrier;

        int ret = pthread_create(&threads[i], NULL, thread_function, args[i]);
        if (ret) {
            fprintf(stderr, "Error creating thread %d\n", i);
            exit(1);
        }
    }

    for (int i = 0; i < P; i++) {
        int ret = pthread_join(threads[i], NULL);
        if (ret) {
            fprintf(stderr, "Error joining thread %d\n", i);
            exit(1);
        }

        free(args[i]);
    }

    // 3. Write output
    write_ppm(scaled_image, argv[2]);

    free_resources(image, scaled_image, contour_map, grid, step_x, barrier);

    return 0;
}
