// FLAGS: g++ -I eigen-3.4.0/ EigenWithFlags.cpp -o Eigen -O3 -march=native -ffast-math -funroll-loops -ftree-vectorize

#include <iostream>
#include <Eigen/Dense>
#include <chrono>
#include <random>
#include <thread>

using namespace Eigen;
using namespace std;
using namespace std::chrono;

// Function to perform matrix multiplication using Eigen library
MatrixXi matrix_multiply(const MatrixXi &A, const MatrixXi &B)
{
    return A * B;
}

int main()
{
    const int size = 100;
    const int range_min = 0;
    const int range_max = 100;

    // Set up random number generation
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(range_min, range_max);

    // Initialize matrices A and B with random values between 0 and 100
    MatrixXi A(size, size);
    MatrixXi B(size, size);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            A(i, j) = dis(gen);
            B(i, j) = dis(gen);
        }
    }

    Eigen::setNbThreads(std::thread::hardware_concurrency()); // Use maximum available threads

    // Start measuring time
    auto start = high_resolution_clock::now();

    // Perform matrix multiplication
    auto result = matrix_multiply(A, B);

    // End measuring time
    auto stop = high_resolution_clock::now();

    // Calculate the duration in milliseconds
    auto duration = duration_cast<milliseconds>(stop - start);

    // Print the time taken for calculation in milliseconds
    cout << duration.count() << endl;

    return 0;
}
