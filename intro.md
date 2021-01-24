# Running these set of examples

## Example 1
`hello_world.cpp` is the canonical hello world, compile it with
```
g++ hello_world.cpp
```
Then run the program with 
```
./a.out
```

`a.out` is the default program name chosen by g++. You can choose a more intelligent name. Try
```
g++ hello_world.cpp -o greeting &&
./greeting
```
The `-o` flag sets the output program name

## Example 2
`hello_world_inc.cpp` is a hello world program that uses a header only library. In this case this is the Eigen library.This means you must provide the correct location of the library. Try
```
g++ hello_world_inc.cpp -I/usr/include/eigen3 -o mathy_greeting &&
./mathy_greeting
```
The `-I` flag sets the include location

## Example 3
`hello_world_lib.cpp` uses a hand-rolled class defined in `HelloWorld.h` with implementation separate in `HelloWorld.cpp`. The implementation must be compiled alongside the main script. Try
```
g++ -Iinclude hello_world_lib.cpp src/HelloWorld.cpp -o classy_greeting &&
./classy_greeting
```

Be sure to use the `-I` flag to bring the `include` folder visible to g++, and compile the `HelloWorld.cpp` file too. Only then will the program be compiled

## Example 4
`hello_world_link.cpp` uses the `boost::program_options` library, which must be linked to shared library `libboost_program_options.so`. Try
```
g++ hello_world_link.cpp -lboost_program_options
```
where the `-l` flag specifies the library name. The names of some libraries may be quite cryptic. Some finesse is needed.

## Example 5
`hello_world_opt.cpp` demonstrates optimization. Compiler optimization is powerful when using a heavily templated library, e.g. Eigen. Try
```
g++ hello_world_opt.cpp -I/usr/include/eigen3 -o inversion_no_opt &&
./inversion_no_opt
```
Note the time needed for the program to run indicated by the printout message. Then try
```
g++ hello_world_opt.cpp -I/usr/include/eigen3 -o inversion_with_opt -O3 &&
./inversion_with_opt
```
Note the performance leap in the latter case. Also inspect the code to learn the usage of the `<chrono>` library for ad hoc timing.

## Example 6
`hello_world_17.cpp` demonstrates bleeding edge c++17 features. Try
```
g++ hello_world_17.cpp -std=c++17 -o black_juju &&
./black_juju
```
The `-std=c++17` flag indicates that the c++17 standard is to be used. Also inspect the code to see that the precise features used are *structured binding*, i.e. decomposing an array (or class, struct, tuple) into individual variables, and the new `std::any` true polymorphic type that can hold ANY data.