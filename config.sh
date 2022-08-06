if [ -d "build" ]
then
    echo "remove build directory."
    rm -r build
fi
mkdir build
# TO DO: add option to detect ninjia generator
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug