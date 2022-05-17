cmake_minimum_required(VERSION 3.12)
project(TopologyLibs)
set(MSVC_FLAGS "/W4;/MP;$<$<CONFIG:DEBUG>:/ZI;/Od>$<$<CONFIG:RELEASE>:/O2>")
set(GNU_FLAGS
    "-Wall;-Werror;-Wextra;-Wpedantic;$<$<CONFIG:DEBUG>:-O0;-g>$<$<CONFIG:RELEASE>:-O3>"
)
set(SRC_FILES
    TopologyAnalysis.cpp
)
set(HEADER_FILES
    TopologyAnalysis.h
)
add_library(Topology STATIC ${HEADER_FILES} ${SRC_FILES})
target_link_libraries(Topology PUBLIC Eigen3::Eigen)
target_include_directories(Topology INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(Topology PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)