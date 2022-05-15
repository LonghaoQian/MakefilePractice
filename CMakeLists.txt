cmake_minimum_required(VERSION 3.12)
project(cmake_template VERSION 1.0.0 LANGUAGES C CXX)

add_compile_options(-Wall)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

set(TOPO_SRC
    src/TopologyAnalysis.cpp
)
add_library(Topology ${TOPO_SRC})
target_include_directories(Topology PUBLIC include)

add_executable(test1 hello_world.cpp)
target_link_libraries(test1 Topology)