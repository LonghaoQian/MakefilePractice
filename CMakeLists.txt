cmake_minimum_required(VERSION 3.15)
project(cmake_template VERSION 1.0.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
# append cmake to module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
# add utility functions
include(utils)
#-------------------- set compile options----------------
# display compiler
if (MSVC)
    message(STATUS "The compiler is MSVC")
else()
    message(STATUS "The compiler is NOT MSVC")
endif()
# save the MSVC files for future use
set(GNU_FLAGS "-Wall;-Werror;-Wextra;-O0;-g;-fno-omit-frame-pointer;-fsanitize=address")
set(MSVC_FLAGS "/W4;/MP;$<$<CONFIG:DEBUG>:/ZI;/Od>$<$<CONFIG:RELEASE>:/O2>")
set(COMPILE_FLAGS "")
string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE_)
if (${BUILD_TYPE_} STREQUAL "debug")
    message("build type is debug")
    set(COMPILE_FLAGS "-Wall;-Werror;-Wextra;-O0;-g;-fno-omit-frame-pointer;-fsanitize=address")
    set(LASAN -lasan)
elseif(${BUILD_TYPE_} STREQUAL "release")
    message("build type is release")
    set(COMPILE_FLAGS "-O3")
    set(LASAN "") # no lasan lib is add in release mode
else()
    # if the build type does not match debug or release, throw an error
    message(FATAL_ERROR "Invalid build type: " ${CMAKE_BUILD_TYPE})
endif()

#---------------- add third party lib ------------------
add_subdirectory(thirdparty)
#------------------- add lib ---------------------------
add_subdirectory(lib)
#------------------- add design mode test -----------------
add_subdirectory(desgin_mode_test)
#------------------ build src -----------------------------
add_subdirectory(src)
# ---------------build tutorial ---------------------------
add_subdirectory(tutorial)
#----------------build test target ------------------------
if (${BUILD_TYPE_} STREQUAL "debug")
    # ut is only built in debug mode
    add_subdirectory(ut)
endif()
#---------------- python binding --------------------
add_subdirectory(python_binding)