#!/bin/sh

# Specify the Conda environment name
CONDA_ENV_NAME="cpp_binding"

# Check if Conda is installed
if ! command -v conda > /dev/null; then
    echo "Conda is not installed or not available in PATH."
    exit 1
fi

# Activate the Conda environment
echo "Activating Conda environment: $CONDA_ENV_NAME"
eval "$(conda shell.bash hook)"  # Enable Conda in a non-interactive shell
conda activate $CONDA_ENV_NAME

# Check if the activation succeeded
if [ "$CONDA_PREFIX" != "" ]; then
    echo "Conda environment activated: $CONDA_PREFIX"
else
    echo "Failed to activate Conda environment."
    exit 1
fi

# Run CMake commands
echo "Configuring CMake with Ninja build system..."
cmake -S . -B build_debug -DCMAKE_BUILD_TYPE=Debug -GNinja \
    -DCMAKE_PREFIX_PATH=/home/longhao/anaconda3/envs/cpp_binding/lib/python3.8/site-packages/pybind11/share/cmake

echo "CMake configuration complete."