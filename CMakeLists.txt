cmake_minimum_required(VERSION 3.12)
project(cmake_template VERSION 1.0.0 LANGUAGES C CXX)
#-------------------- set compile options----------------
set(CMAKE_CXX_STANDARD 17)
set(MSVC_FLAGS "/W4;/MP;$<$<CONFIG:DEBUG>:/ZI;/Od>$<$<CONFIG:RELEASE>:/O2>")
set(GNU_FLAGS
    "-Wall;-Werror;-Wextra;-Wpedantic;$<$<CONFIG:DEBUG>:-O0;-g>$<$<CONFIG:RELEASE>:-O3>"
)
#---------------- add third party lib ------------------
add_subdirectory(thirdparty)
#------------------- add lib ---------------------------
add_subdirectory(graphtools)
# display compiler
if (MSVC)
    message("-- The compiler is MSVC")
else()
    message("-- The compiler is NOT MSVC")
endif()
# display build type
message("-- build type is set to " ${CMAKE_BUILD_TYPE})
#--------------- build target --------------------------
add_executable(test1 src/tarjan_method_test.cpp)
target_link_libraries(test1 PUBLIC GraphAnalysis)
target_compile_options(test1 PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)
add_executable(test2 src/johnson_curcit_test.cpp)
target_link_libraries(test2 PUBLIC GraphAnalysis)
target_compile_options(test2 PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)