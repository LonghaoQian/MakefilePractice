cmake_minimum_required(VERSION 3.12)
project(cmake_template VERSION 1.0.0 LANGUAGES C CXX)

add_subdirectory(thirdparty)
add_subdirectory(lib)

set(CMAKE_CXX_STANDARD 17)
set(MSVC_FLAGS "/W4;/MP;$<$<CONFIG:DEBUG>:/ZI;/Od>$<$<CONFIG:RELEASE>:/O2>")
set(GNU_FLAGS
    "-Wall;-Werror;-Wextra;-Wpedantic;$<$<CONFIG:DEBUG>:-O0;-g>$<$<CONFIG:RELEASE>:-O3>"
)
if (MSVC)
    message("The compiler is MSVC")
else()
    message("The compiler is NOT MSVC")
endif()

add_executable(test1 hello_world.cpp)
target_link_libraries(test1 PUBLIC Topology)
target_compile_options(test1 PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)