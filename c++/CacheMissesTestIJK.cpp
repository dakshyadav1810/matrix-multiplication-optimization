#include <iostream>
#include <chrono>

const int SIZE = 100;

// Function to multiply two matrices of 1s using 2D arrays
void matrix_multiply_2d(int A[][SIZE], int B[][SIZE], int C[][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for (int k = 0; k < SIZE; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
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
        }
    }

    // Start timing
    auto start = std::chrono::steady_clock::now();

    // Multiply matrices
    matrix_multiply_2d(A, B, C);

    // End timing
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << std::chrono::duration<double, std::milli>(diff).count() << std::endl;

    return 0;
}
