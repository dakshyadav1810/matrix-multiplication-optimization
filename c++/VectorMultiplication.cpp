#include <iostream>
#include <vector>
#include <chrono> // For timing

using namespace std;
using namespace std::chrono;

// Function to perform matrix multiplication
vector<vector<int>> matrix_multiply(const vector<vector<int>> &mat1, const vector<vector<int>> &mat2)
{
    int rows1 = mat1.size();
    int cols1 = mat1[0].size();
    int rows2 = mat2.size();
    int cols2 = mat2[0].size();

    if (cols1 != rows2)
    {
        cout << "Cannot multiply matrices. Invalid dimensions.";
        return {};
    }

    vector<vector<int>> result(rows1, vector<int>(cols2, 0));

    for (int i = 0; i < rows1; ++i)
    {
        for (int j = 0; j < cols2; ++j)
        {
            for (int k = 0; k < cols1; ++k)
            {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return result;
}

int main()
{
    // Initialize two 100x100 matrices with random values
    vector<vector<int>> mat1(100, vector<int>(100, 1)); // All elements are 1 for simplicity
    vector<vector<int>> mat2(100, vector<int>(100, 1)); // All elements are 1 for simplicity

    // Measure the time taken for multiplication
    auto start = high_resolution_clock::now();
    vector<vector<int>> result = matrix_multiply(mat1, mat2);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << duration.count() << endl;

    return 0;
}
