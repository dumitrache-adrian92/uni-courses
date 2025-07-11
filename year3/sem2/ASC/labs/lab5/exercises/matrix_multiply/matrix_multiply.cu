
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <vector>

#define TILE_WIDTH 16

// TODO 1 - simple matrix multiplication
__global__ void matrix_multiply_simple(float *ma, float *mb, float *mc,
                                       size_t width) {
  // TODO: calculate the row & column index of the element
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  int col = blockIdx.x * blockDim.x + threadIdx.x;

  // TODO: do dot product between row of ma and column of mb
  if (row >= width || col >= width) {
    return;
  }

  float result = 0;
  for (int k = 0; k < width; ++k) {
    result += ma[row * width + k] * mb[k * width + col];
  }

  // TODO: write result in mc
  mc[row * width + col] = result;
}

// TODO 2 - optimized matrix multiplication
__global__ void matrix_multiply(float *ma, float *mb, float *mc, size_t width) {
  // create shorthand names for threadIdx & blockIdx
  int tx = threadIdx.x, ty = threadIdx.y;
  int bx = blockIdx.x, by = blockIdx.y;

  // TODO: allocate 2D tiles in __shared__ memory
  __shared__ float tile_a[TILE_WIDTH][TILE_WIDTH];
  __shared__ float tile_b[TILE_WIDTH][TILE_WIDTH];

  // TODO: calculate the row & column index of the element
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  int col = blockIdx.x * blockDim.x + threadIdx.x;

  float result = 0;

  if (row >= width || col >= width) {
    return;
  }

  // loop over the tiles of the input in phases
  for (int t = 0; t < width / TILE_WIDTH; ++t) {
    // TODO: load tiles into __shared__ memory allocated before
    tile_a[ty][tx] = ma[row * width + t * TILE_WIDTH + tx];
    tile_b[ty][tx] = mb[(t * TILE_WIDTH + ty) * width + col];

    // TODO:
    //  wait until all data is loaded before allowing
    //  any thread in this block to continue
    __syncthreads();

    // TODO: do dot product between row of tile from ma and column of tile from
    // mb
    for (int k = 0; k < TILE_WIDTH; ++k) {
      result += tile_a[ty][k] * tile_b[k][tx];
    }

    // TODO:
    //  wait until all data is loaded before allowing
    //  any thread in this block to continue
    __syncthreads();
  }

  // TODO: write result in mc
  mc[row * width + col] = result;
}

int main(void) {
  // create a large workload so we can easily measure the
  // performance difference of both implementations

  // note that n measures the width of the matrix, not the number of total
  // elements
  const size_t n = 1 << 10;
  const dim3 block_size(TILE_WIDTH, TILE_WIDTH);
  const dim3 num_blocks(n / block_size.x, n / block_size.y);

  // generate random input on the host
  std::vector<float> host_a(n * n), host_b(n * n), host_c(n * n);
  for (int i = 0; i < n * n; ++i) {
    host_a[i] = static_cast<float>(rand()) / RAND_MAX;
    host_b[i] = static_cast<float>(rand()) / RAND_MAX;
  }

  // allocate storage for the device
  float *device_a = 0, *device_b = 0, *device_c = 0;
  cudaMalloc((void **)&device_a, sizeof(float) * n * n);
  cudaMalloc((void **)&device_b, sizeof(float) * n * n);
  cudaMalloc((void **)&device_c, sizeof(float) * n * n);

  // copy input to the device
  cudaMemcpy(device_a, &host_a[0], sizeof(float) * n * n,
             cudaMemcpyHostToDevice);
  cudaMemcpy(device_b, &host_b[0], sizeof(float) * n * n,
             cudaMemcpyHostToDevice);

  // TODO 3 - measure the time spent in the kernel for simple and optimized
  // implementation

  // TODO: create CUDA events for measuring kernel time
  cudaEvent_t launch_begin, launch_end;

  cudaEventCreate(&launch_begin);
  cudaEventCreate(&launch_end);

  // time many kernel launches and take the average time
  const size_t num_launches = 100;
  float average_simple_time = 0;
  std::cout << "Timing simple implementation...";

  for (int i = 0; i < num_launches; ++i) {
    // TODO: record CUDA event before and after the kernel launch
    cudaEventRecord(launch_begin);


    matrix_multiply_simple<<<num_blocks, block_size>>>(device_a, device_b,
                                                       device_c, n);

    // TODO: Wait for launch_end event to complete
    cudaEventRecord(launch_end);
    cudaEventSynchronize(launch_end);

    // TODO: measure the time spent in the kernel
    float time = 0;
    cudaEventElapsedTime(&time, launch_begin, launch_end);

    average_simple_time += time;
  }

  average_simple_time /= num_launches;
  std::cout << " done." << std::endl;

  // now time the optimized kernel

  // time many kernel launches and take the average time
  float average_optimized_time = 0;
  std::cout << "Timing optimized implementation...";
  for (int i = 0; i < num_launches; ++i) {
    // TODO: record CUDA event before and after the kernel launch
    cudaEventRecord(launch_begin);

    matrix_multiply<<<num_blocks, block_size>>>(device_a, device_b, device_c,
                                                n);

    // TODO: Wait for launch_end event to complete
    cudaEventRecord(launch_end);
    cudaEventSynchronize(launch_end);

    // TODO: measure the time spent in the kernel
    float time = 0;
    cudaEventElapsedTime(&time, launch_begin, launch_end);

    average_optimized_time += time;
  }

  average_optimized_time /= num_launches;
  std::cout << " done." << std::endl;

  // report the effective throughput of each kernel in GFLOPS
  // the effective throughput is measured as the number of floating point
  // operations performed per second: (one mul + one add) * N^3
  float simple_throughput = static_cast<float>(2 * n * n * n) /
                            (average_simple_time / 1000.0f) / 1000000000.0f;
  float optimized_throughput = static_cast<float>(2 * n * n * n) /
                               (average_optimized_time / 1000.0f) /
                               1000000000.0f;

  std::cout << "Matrix size: " << n << "x" << n << std::endl;
  std::cout << "Tile size: " << TILE_WIDTH << "x" << TILE_WIDTH << std::endl;

  std::cout << "Throughput of simple kernel: " << simple_throughput << " GFLOPS"
            << std::endl;
  std::cout << "Throughput of optimized kernel: " << optimized_throughput
            << " GFLOPS" << std::endl;
  std::cout << "Performance improvement: "
            << optimized_throughput / simple_throughput << "x" << std::endl;
  std::cout << std::endl;

  // TODO: destroy the CUDA events
  cudaEventDestroy(launch_begin);
  cudaEventDestroy(launch_end);

  // deallocate device memory
  cudaFree(device_a);
  cudaFree(device_b);
  cudaFree(device_c);

  return 0;
}
