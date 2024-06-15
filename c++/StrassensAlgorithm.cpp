#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to add two matrices
void add_matrices(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C)
{
    int n = A.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to subtract two matrices
void subtract_matrices(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C)
{
    int n = A.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Function to multiply two matrices using Strassen algorithm
void strassen_multiply(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C)
{
    int n = A.size();

    // Base case: If the matrix size is 1x1
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    // Allocate memory for submatrices
    vector<vector<int>> A11(n / 2, vector<int>(n / 2));
    vector<vector<int>> A12(n / 2, vector<int>(n / 2));
    vector<vector<int>> A21(n / 2, vector<int>(n / 2));
    vector<vector<int>> A22(n / 2, vector<int>(n / 2));
    vector<vector<int>> B11(n / 2, vector<int>(n / 2));
    vector<vector<int>> B12(n / 2, vector<int>(n / 2));
    vector<vector<int>> B21(n / 2, vector<int>(n / 2));
    vector<vector<int>> B22(n / 2, vector<int>(n / 2));
    vector<vector<int>> C11(n / 2, vector<int>(n / 2));
    vector<vector<int>> C12(n / 2, vector<int>(n / 2));
    vector<vector<int>> C21(n / 2, vector<int>(n / 2));
    vector<vector<int>> C22(n / 2, vector<int>(n / 2));
    vector<vector<int>> M1(n / 2, vector<int>(n / 2));
    vector<vector<int>> M2(n / 2, vector<int>(n / 2));
    vector<vector<int>> M3(n / 2, vector<int>(n / 2));
    vector<vector<int>> M4(n / 2, vector<int>(n / 2));
    vector<vector<int>> M5(n / 2, vector<int>(n / 2));
    vector<vector<int>> M6(n / 2, vector<int>(n / 2));
    vector<vector<int>> M7(n / 2, vector<int>(n / 2));
    vector<vector<int>> temp1(n / 2, vector<int>(n / 2));
    vector<vector<int>> temp2(n / 2, vector<int>(n / 2));

    // Divide matrices into submatrices
    for (int i = 0; i < n / 2; ++i)
    {
        for (int j = 0; j < n / 2; ++j)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + n / 2];
            A21[i][j] = A[i + n / 2][j];
            A22[i][j] = A[i + n / 2][j + n / 2];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + n / 2];
            B21[i][j] = B[i + n / 2][j];
            B22[i][j] = B[i + n / 2][j + n / 2];
        }
    }

    // Compute intermediate matrices
    add_matrices(A11, A22, temp1);
    add_matrices(B11, B22, temp2);
    strassen_multiply(temp1, temp2, M1);

    add_matrices(A21, A22, temp1);
    strassen_multiply(temp1, B11, M2);

    subtract_matrices(B12, B22, temp2);
    strassen_multiply(A11, temp2, M3);

    subtract_matrices(B21, B11, temp2);
    strassen_multiply(A22, temp2, M4);

    add_matrices(A11, A12, temp1);
    strassen_multiply(temp1, B22, M5);

    subtract_matrices(A21, A11, temp1);
    add_matrices(B11, B12, temp2);
    strassen_multiply(temp1, temp2, M6);

    subtract_matrices(A12, A22, temp1);
    add_matrices(B21, B22, temp2);
    strassen_multiply(temp1, temp2, M7);

    // Compute result submatrices
    add_matrices(M1, M4, temp1);
    subtract_matrices(temp1, M5, temp2);
    add_matrices(temp2, M7, C11);

    add_matrices(M3, M5, C12);

    add_matrices(M2, M4, C21);

    add_matrices(M1, M3, temp1);
    subtract_matrices(temp1, M2, temp2);
    add_matrices(temp2, M6, C22);

    // Combine result submatrices into the final result matrix
    for (int i = 0; i < n / 2; ++i)
    {
        for (int j = 0; j < n / 2; ++j)
        {
            C[i][j] = C11[i][j];
            C[i][j + n / 2] = C12[i][j];
            C[i + n / 2][j] = C21[i][j];
            C[i + n / 2][j + n / 2] = C22[i][j];
        }
    }
}

// Function to multiply two matrices using Strassen algorithm
vector<vector<int>> strassen_multiply(const vector<vector<int>> &A, const vector<vector<int>> &B)
{
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    strassen_multiply(A, B, C);
    return C;
}

// Function to multiply two matrices using regular algorithm
vector<vector<int>> regular_multiply(const vector<vector<int>> &A, const vector<vector<int>> &B)
{
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

int main()
{
    const int n = 100;
    vector<vector<int>> A(n, vector<int>(n, 1)); // All elements are 1 for simplicity
    vector<vector<int>> B(n, vector<int>(n, 1)); // All elements are 1 for simplicity

    srand(time(nullptr)); // Seed the random number generator
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            A[i][j] = static_cast<int>(rand() % 100); // Random value between 0 and 99
            B[i][j] = static_cast<int>(rand() % 100);
        }
    }

    auto start = high_resolution_clock::now();
    vector<vector<int>> result_strassen = strassen_multiply(A, B);
    auto stop = high_resolution_clock::now();
    auto duration_strassen = duration_cast<milliseconds>(stop - start);

    start = high_resolution_clock::now();
    vector<vector<int>> result_regular = regular_multiply(A, B);
    stop = high_resolution_clock::now();
    auto duration_regular = duration_cast<milliseconds>(stop - start);

    cout << duration_strassen.count() << endl;

    return 0;
}
