#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

// A simple function that processes a NumPy array
double sum_array(py::array_t<double> input_array) {
    // Ensure the input array is contiguous and has the correct data type
    auto buf = input_array.request();

    // Check for 1D array
    if (buf.ndim != 1) {
        throw std::runtime_error("Input array must be 1-dimensional.");
    }

    // Pointer to the data
    double* ptr = static_cast<double*>(buf.ptr);

    // Compute the sum
    double sum = 0.0;
    for (int32_t i = 0; i < buf.shape[0]; i++) {
        sum += ptr[i];
    }
    return sum;
}

// Bind the function to Python: module name is pybind_test. This has to be 
// correct
PYBIND11_MODULE(pybind_test, m) {
    m.def("sum_array", &sum_array, "A function that sums a 1D NumPy array");
}