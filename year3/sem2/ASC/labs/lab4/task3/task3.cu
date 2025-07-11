#include <stdio.h>
#include "utils.h"

/**
 * ~TODO 3~
 * Modify the kernel below such as each element of the
 * array will be now equal to 0 if it is an even number
 * or 1, if it is an odd number
 */
__global__ void kernel_parity_id(int *a, int N) {
    unsigned int i = threadIdx.x + blockDim.x * blockIdx.x;
    if (i < N) {
        int val = a[i] % 2;
        a[i] = val;
    }
}

/**
 * ~TODO 4~
 * Modify the kernel below such as each element will
 * be equal to the BLOCK ID this computation takes
 * place.
 */
__global__ void kernel_block_id(int *a, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) {
        a[i] = blockIdx.x;
    }
}

/**
 * ~TODO 5~
 * Modify the kernel below such as each element will
 * be equal to the THREAD ID this computation takes
 * place.
 */
__global__ void kernel_thread_id(int *a, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) {
        a[i] = threadIdx.x;
    }
}

int main(void) {
    int nDevices;

    // Get the number of CUDA-capable GPU(s)
    cudaGetDeviceCount(&nDevices);

    /**
     * ~TODO 1~
     * For each device, show some details in the format below,
     * then set as active device the first one (assuming there
     * is at least CUDA-capable device). Pay attention to the
     * type of the fields in the cudaDeviceProp structure.
     *
     * Device number: <i>
     *      Device name: <name>
     *      Total memory: <mem>
     *      Memory Clock Rate (KHz): <mcr>
     *      Memory Bus Width (bits): <mbw>
     *
     * Hint: look for cudaGetDeviceProperties and cudaSetDevice in
     * the Cuda Toolkit Documentation.
     */
    // cudaDeviceProp* prop;
    // for (int i = 0; i < nDevices; ++i) {
    //     cudaGetDeviceProperties(prop, i);

    //     puts(prop->name);
    //     printf("%lu\n", prop->totalGlobalMem);
    //     printf("%d\n", prop->memoryClockRate);
    //     printf("%d\n", prop->memoryBusWidth);
    // }

    cudaSetDevice(0);

    /**
     * ~TODO 2~
     * With information from example_2.cu, allocate an array with
     * integers (where a[i] = i). Then, modify the three kernels
     * above and execute them using 4 blocks, each with 4 threads.
     *
     * You can use the fill_array(int *a, int n) function (from utils)
     * to fill your array as many times you want.
     *
     *  ~TODO 3~
     * Execute kernel_parity_id kernel and then copy from
     * the device to the host; call cudaDeviceSynchronize()
     * after a kernel execution for safety purposes.
     */
    int N = 16;
    int *host_array = 0;
    host_array = (int *) malloc(N * sizeof(int));
    const size_t block_size = 4;
    size_t blocks_no = N / block_size;

    if (N % block_size)
        ++blocks_no;

    fill_array_int(host_array, N);

    int *device_array = 0;
    cudaMalloc((void **) &device_array, N * sizeof(int));
    cudaMemcpy(device_array, host_array, N * sizeof(int), cudaMemcpyHostToDevice);

    kernel_parity_id<<<blocks_no, block_size>>>(device_array, N);
    cudaDeviceSynchronize();

    cudaMemcpy(host_array, device_array, N * sizeof(int), cudaMemcpyDeviceToHost);

    check_task_2(3, host_array);


    /**
     * ~TODO 4~
     * Execute kernel_block_id kernel and then copy from
     * the device to the host;
     */
    fill_array_int(host_array, N);
    cudaMemcpy(device_array, host_array, N * sizeof(int), cudaMemcpyHostToDevice);

    kernel_block_id<<<blocks_no, block_size>>>(device_array, N);
    cudaDeviceSynchronize();

    cudaMemcpy(host_array, device_array, N * sizeof(int), cudaMemcpyDeviceToHost);

    check_task_2(4, host_array);

    /**
     * ~TODO 5~
     * Execute kernel_thread_id kernel and then copy from
     * the device to the host;
     */
    fill_array_int(host_array, N);
    cudaMemcpy(device_array, host_array, N * sizeof(int), cudaMemcpyHostToDevice);

    kernel_thread_id<<<blocks_no, block_size>>>(device_array, N);
    cudaDeviceSynchronize();

    cudaMemcpy(host_array, device_array, N * sizeof(int), cudaMemcpyDeviceToHost);

    check_task_2(5, host_array);

    // TODO 6: Free the memory
    free(host_array);
    // free(host_array_result);
    cudaFree(device_array);

    return 0;
}