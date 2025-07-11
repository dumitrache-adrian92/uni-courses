#include <stdio.h>
#include <math.h>
#include "utils.h"

// TODO 6: Write the code to add the two arrays element by element and
// store the result in another array
__global__ void add_arrays(const float *a, const float *b, float *c, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < N)
        c[i] = a[i] + b[i];
}

int main(void) {
    cudaSetDevice(0);
    int N = 1 << 20;

    float *host_array_a = 0;
    float *host_array_b = 0;
    float *host_array_c = 0;

    float *device_array_a = 0;
    float *device_array_b = 0;
    float *device_array_c = 0;

    // TODO 1: Allocate the host's arrays
    host_array_a = (float *) malloc(N * sizeof(float));
    host_array_b = (float *) malloc(N * sizeof(float));
    host_array_c = (float *) malloc(N * sizeof(float));

    // TODO 2: Allocate the device's arrays
    cudaError aErr = cudaMalloc((void **) &device_array_a, N * sizeof(float));
    cudaError bErr = cudaMalloc((void **) &device_array_b, N * sizeof(float));
    cudaError cErr = cudaMalloc((void **) &device_array_c, N * sizeof(float));

    // TODO 3: Check for allocation errors
    if (device_array_a == NULL || device_array_b == NULL || device_array_c == NULL) {
        perror("malloc");
        exit(1);
    }

    if (aErr != cudaSuccess || bErr != cudaSuccess || cErr != cudaSuccess) {
        perror("cudaMalloc");
        exit(1);
    }

    // TODO 4: Fill array with values; use fill_array_float to fill
    // host_array_a and fill_array_random to fill host_array_b. Each
    // function has the signature (float *a, int n), where n = the size.
    fill_array_float(host_array_a, N);
    fill_array_random(host_array_b, N);

    // TODO 5: Copy the host's arrays to device
    cudaMemcpy(device_array_a, host_array_a, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(device_array_b, host_array_b, N * sizeof(float), cudaMemcpyHostToDevice);

    // TODO 6: Execute the kernel, calculating first the grid size
    // and the amount of threads in each block from the grid
    const size_t block_size = 256;
    size_t blocks_no = N / block_size;

    if (N % block_size)
        ++blocks_no;

    add_arrays<<<blocks_no, block_size>>>(device_array_a, device_array_b, device_array_c, N);

    // TODO 7: Copy back the results and then uncomment the checking function
    cudaMemcpy(host_array_c, device_array_c, N * sizeof(float), cudaMemcpyDeviceToHost);

    check_task_3(host_array_a, host_array_b, host_array_c, N);

    // TODO 8: Free the memory
    free(host_array_a);
    free(host_array_b);
    free(host_array_c);
    cudaFree(device_array_a);
    cudaFree(device_array_b);
    cudaFree(device_array_c);

    return 0;
}