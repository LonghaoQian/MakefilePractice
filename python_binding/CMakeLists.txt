message(STATUS "configuring pybind11...")
# Find pybind11 in the Conda environment
message(STATUS "conada_prefix: $ENV{CONDA_PREFIX}")
if(DEFINED ENV{CONDA_PREFIX})
    set(CONDA_INCLUDE_DIR $ENV{CONDA_PREFIX}/include)
    set(CONDA_LIBRARY_DIR $ENV{CONDA_PREFIX}/lib)
endif()


# Add the pybind11 include directory
include_directories(${CONDA_INCLUDE_DIR})

set(Python3_EXECUTABLE "/home/longhao/anaconda3/envs/cpp_binding/bin/python3")
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Find pybind11 package (if using CMake's pybind11)
find_package(pybind11 REQUIRED PATHS ${CONDA_LIBRARY_DIR}/pybind11)

# add the test target

pybind11_add_module(pybind_test single_function_binding.cpp)

# add_single_exc(TARGET simple_pybind_test
#                SOURCE single_function_binding.cpp
#                LIBRARIES ${LASAN}; pybind11::module
#                COMPILE_OPTIONS ${COMPILE_FLAGS})

target_include_directories(pybind_test PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(pybind_test PRIVATE ${Python3_LIBRARIES})