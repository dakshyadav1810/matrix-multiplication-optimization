import time
import random


def regular_matrix_multiplication(A, B):
    if len(A[0]) != len(B):
        raise ValueError("Number of columns in A must be equal to number of rows in B")

    # Determine dimensions of resulting matrix
    rows_A = len(A)
    cols_B = len(B[0])
    result = [[0] * cols_B for _ in range(rows_A)]

    # Perform matrix multiplication
    for i in range(rows_A):
        for j in range(cols_B):
            for k in range(len(B)):
                result[i][j] += A[i][k] * B[k][j]

    return result


# Generate large random matrices
size = 100
A = [[random.randint(0, 99) for _ in range(size)] for _ in range(size)]
B = [[random.randint(0, 99) for _ in range(size)] for _ in range(size)]

# Calculate time for matrix multiplication
start_time = time.time()
result_regular = regular_matrix_multiplication(A, B)
end_time = time.time()
regular_time = (end_time - start_time) * 1000  # Convert to milliseconds
print(regular_time)
