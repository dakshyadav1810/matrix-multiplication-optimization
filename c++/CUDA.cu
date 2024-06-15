#include <iostream>
#include <chrono>

const int SIZE = 100;
const int BLOCK_SIZE = 16;

// CUDA kernel to perform matrix multiplication with shared memory
__global__ void matrix_multiply_cuda(int *A, int *B, int *C, int size)
{
    __shared__ int As[BLOCK_SIZE][BLOCK_SIZE];
    __shared__ int Bs[BLOCK_SIZE][BLOCK_SIZE];

    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    int val = 0;
    for (int m = 0; m < size / BLOCK_SIZE; ++m)
    {
        // Load data into shared memory
        As[threadIdx.y][threadIdx.x] = A[row * size + (m * BLOCK_SIZE + threadIdx.x)];
        Bs[threadIdx.y][threadIdx.x] = B[(m * BLOCK_SIZE + threadIdx.y) * size + col];
        __syncthreads();

        // Compute the matrix multiplication within the block
        for (int k = 0; k < BLOCK_SIZE; ++k)
        {
            val += As[threadIdx.y][k] * Bs[k][threadIdx.x];
        }
        __syncthreads();
    }

    C[row * size + col] = val;
}

int main()
{
    int A[SIZE][SIZE];
    int B[SIZE][SIZE];
    int C[SIZE][SIZE];

    // Initialize matrices with 1s
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            A[i][j] = 1;
            B[i][j] = 1;
            C[i][j] = 0; // Initialize result matrix to 0
        }
    }

    // Declare device pointers
    int *d_A, *d_B, *d_C;

    // Allocate device memory
    cudaMalloc(&d_A, SIZE * SIZE * sizeof(int));
    cudaMalloc(&d_B, SIZE * SIZE * sizeof(int));
    cudaMalloc(&d_C, SIZE * SIZE * sizeof(int));

    // Copy input matrices from host to device
    cudaMemcpy(d_A, A, SIZE * SIZE * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, SIZE * SIZE * sizeof(int), cudaMemcpyHostToDevice);

    // Define grid and block dimensions
    dim3 threadsPerBlock(BLOCK_SIZE, BLOCK_SIZE); // 16x16 threads per block
    dim3 numBlocks((SIZE + threadsPerBlock.x - 1) / threadsPerBlock.x, (SIZE + threadsPerBlock.y - 1) / threadsPerBlock.y);

    // Start timing
    auto start = std::chrono::steady_clock::now();

    // Launch CUDA kernel
    matrix_multiply_cuda<<<numBlocks, threadsPerBlock>>>(d_A, d_B, d_C, SIZE);

    // End timing
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << std::chrono::duration<double, std::milli>(diff).count() << std::endl;

    // Copy result matrix from device to host
    cudaMemcpy(C, d_C, SIZE * SIZE * sizeof(int), cudaMemcpyDeviceToHost);

    // Free device memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
