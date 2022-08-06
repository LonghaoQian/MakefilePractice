if [ -d "build" ]
then
    echo "remove build directory."
    rm -r build
fi
mkdir build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build