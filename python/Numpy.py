"""
Numpy already uses a bunch of different software and hardware optimizations for its numpy.dot() function. 
This is already one of the most efficient ways of matrix multiplication. So for this task, I will be using this as a benchmark. 
The average time for a 100x100 random matrix multiplication is around 1.002 milliseconds.
"""

import numpy as np
import time
import random

# Generate large random matrices
size = 1000
A = [[random.randint(0, 99) for _ in range(size)] for _ in range(size)]
B = [[random.randint(0, 99) for _ in range(size)] for _ in range(size)]

size = 1000
A = np.random.rand(size, size)
B = np.random.rand(size, size)

# Calculate time for NumPy's built-in matrix multiplication
start_time = time.time()
result_numpy = np.dot(A, B)
end_time = time.time()
numpy_time = (end_time - start_time) * 1000  # Convert to milliseconds
print(numpy_time)
