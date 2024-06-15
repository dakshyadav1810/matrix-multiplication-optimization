import random
import time


def add_matrix(A, B):
    n = len(A)
    C = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            C[i][j] = A[i][j] + B[i][j]
    return C


def subtract_matrix(A, B):
    n = len(A)
    C = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            C[i][j] = A[i][j] - B[i][j]
    return C


def strassen_multiply(A, B):
    n = len(A)

    # Base case: If the matrix size is 1x1
    if n == 1:
        return [[A[0][0] * B[0][0]]]

    # Divide matrices into quadrants
    newSize = n // 2
    A11 = [[0] * newSize for _ in range(newSize)]
    A12 = [[0] * newSize for _ in range(newSize)]
    A21 = [[0] * newSize for _ in range(newSize)]
    A22 = [[0] * newSize for _ in range(newSize)]
    B11 = [[0] * newSize for _ in range(newSize)]
    B12 = [[0] * newSize for _ in range(newSize)]
    B21 = [[0] * newSize for _ in range(newSize)]
    B22 = [[0] * newSize for _ in range(newSize)]

    for i in range(newSize):
        for j in range(newSize):
            A11[i][j] = A[i][j]
            A12[i][j] = A[i][j + newSize]
            A21[i][j] = A[i + newSize][j]
            A22[i][j] = A[i + newSize][j + newSize]

            B11[i][j] = B[i][j]
            B12[i][j] = B[i][j + newSize]
            B21[i][j] = B[i + newSize][j]
            B22[i][j] = B[i + newSize][j + newSize]

    # Compute intermediate matrices
    M1 = strassen_multiply(add_matrix(A11, A22), add_matrix(B11, B22))
    M2 = strassen_multiply(add_matrix(A21, A22), B11)
    M3 = strassen_multiply(A11, subtract_matrix(B12, B22))
    M4 = strassen_multiply(A22, subtract_matrix(B21, B11))
    M5 = strassen_multiply(add_matrix(A11, A12), B22)
    M6 = strassen_multiply(subtract_matrix(A21, A11), add_matrix(B11, B12))
    M7 = strassen_multiply(subtract_matrix(A12, A22), add_matrix(B21, B22))

    # Compute result quadrants
    C11 = add_matrix(subtract_matrix(add_matrix(M1, M4), M5), M7)
    C12 = add_matrix(M3, M5)
    C21 = add_matrix(M2, M4)
    C22 = add_matrix(subtract_matrix(add_matrix(M1, M3), M2), M6)

    # Combine result quadrants into the final result matrix
    result = [[0] * n for _ in range(n)]
    for i in range(newSize):
        for j in range(newSize):
            result[i][j] = C11[i][j]
            result[i][j + newSize] = C12[i][j]
            result[i + newSize][j] = C21[i][j]
            result[i + newSize][j + newSize] = C22[i][j]

    return result


# Generate random matrices of size 100x100
size = 100
A = [[random.randint(0, 99) for _ in range(size)] for _ in range(size)]
B = [[random.randint(0, 99) for _ in range(size)] for _ in range(size)]

# Measure the time for Strassen matrix multiplication
start_time = time.time()
result = strassen_multiply(A, B)
end_time = time.time()
duration = (end_time - start_time) * 1000  # Convert to milliseconds

print(duration)
