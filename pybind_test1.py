import pybind_test

import numpy as np

# Create a NumPy array
array = np.array([1.0, 2.0, 3.0, 4.0])

# Call the C++ function via the Python module
result = pybind_test.sum_array(array)

print(f"Result from C++ library: {result}")
