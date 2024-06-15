#include <iostream>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

// Function to multiply two matrices
void multiply_matrices(int A[][100], int B[][100], int result[][100], int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            result[i][j] = 0;
            for (int k = 0; k < size; ++k)
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    const int size = 100;
    int A[size][size];
    int B[size][size];
    int result[size][size];

    // Fill matrices A and B with random values
    srand(time(nullptr)); // Seed the random number generator
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            A[i][j] = static_cast<int>(rand() % 100); // Random value between 0 and 99
            B[i][j] = static_cast<int>(rand() % 100);
        }
    }

    // Multiply matrices A and B and measure time
    auto start = high_resolution_clock::now();
    multiply_matrices(A, B, result, size);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << duration.count() << endl;

    return 0;
}
