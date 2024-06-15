import subprocess
import itertools
import sys

print("============================================================================")
print("                  MATMUL Benchmarking Tool - KOSS Task")
print("============================================================================")
print(
    """
This tool runs scripts that explore different ways to optimize Matrix Multiplication. 
These optimizations involve techniques such as managing memory efficiently, running computations in parallel, 
utilizing CUDA cores, and using BLAS functions.

Each script runs 100 times, generating two 100x100 square matrices and calculating their product. 
We then average the time taken for each run and display it. This information helps us make informed decisions 
about which optimization approach to pursue further.

For more details about each optimization approach, you can check out the report slides in this repository.
"""
)
print("Press Enter to start the tests...")
input()

num_runs = 100

script_paths = [
    "python ./python/Naive.py",
    "python ./python/Numpy.py",
    "python ./python/StrassenInPy.py",
    "./executables/naive",
    "./executables/vectorMultiplication",
    "./executables/Eigen",
    "./executables/WithoutEigen",
    "./executables/CacheMissesTestIJK",
    "./executables/CacheMissesTestKIJ",
    "./executables/CUDA",
    "./executables/CUDA-Flags",
    "./executables/CUDA-Flags-Unrolled",
    "./executables/CUDA-Flags-BLAS",
]

averages = {}

animation_frames = itertools.cycle(["-", "\\", "|", "/"])

for idx, script_path in enumerate(script_paths, 1):
    print("Running", script_path)
    results = []
    for i in range(num_runs):
        progress = (i + 1) / num_runs
        bar_width = 50
        num_chars = int(bar_width * progress)
        loading_bar = "[" + "#" * num_chars + "-" * (bar_width - num_chars) + "]"

        # Print the loading bar
        sys.stdout.write("\r{} {:.2f}%".format(loading_bar, progress * 100))
        sys.stdout.flush()

        # Run the script and capture its output
        if "python" in script_path:
            result = subprocess.check_output(
                ["python", script_path.split(" ")[1]], universal_newlines=True
            )
        else:
            result = subprocess.check_output([script_path], universal_newlines=True)
        results.append(float(result.strip()))

    average = sum(results) / num_runs

    print("\nAverage for", script_path, ":", average, "ms")

    # Print a newline to clear the animation
    print()
