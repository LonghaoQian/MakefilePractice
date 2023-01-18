cmake_minimum_required(VERSION 3.15)
project(cmake_template VERSION 1.0.0 LANGUAGES C CXX)
#-------------------- set compile options----------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(MSVC_FLAGS "/W4;/MP;$<$<CONFIG:DEBUG>:/ZI;/Od>$<$<CONFIG:RELEASE>:/O2>")
set(GNU_FLAGS
    "-Wall;-Werror;-Wextra;-Wpedantic;$<$<CONFIG:DEBUG>:-O0;-g;-fno-omit-frame-pointer;-fsanitize=address>$<$<CONFIG:RELEASE>:-O3>;"
)
#---------------- add third party lib ------------------
add_subdirectory(thirdparty)
#------------------- add lib ---------------------------
add_subdirectory(lib)
#------------------- add design mode test ---------------------------
add_subdirectory(desgin_mode_test)
# display compiler
if (MSVC)
    message("-- The compiler is MSVC")
else()
    message("-- The compiler is NOT MSVC")
endif()
# display build type
message("-- build type is set to " ${CMAKE_BUILD_TYPE})
# add utility functions
include(cmake/utils.cmake)

#--------------- build target --------------------------
add_executable(test1 src/tarjan_method_test.cpp)
target_link_libraries(test1 PUBLIC GraphAnalysis -lasan)
target_compile_options(test1 PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)
add_executable(test2 src/johnson_curcit_test.cpp)
target_link_libraries(test2 PUBLIC GraphAnalysis -lasan)
target_compile_options(test2 PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)
add_executable(test3 src/dijstra_test.cpp)
target_link_libraries(test3 PUBLIC GraphAnalysis -lasan)
target_compile_options(test3 PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)
add_executable(test4 src/singleton_test.cpp)
target_link_libraries(test4 PUBLIC -Wl,--whole-archive module_factory -Wl,--no-whole-archive -lasan)
target_compile_options(test4 PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                      $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)

add_executable(test5 src/rotation_test.cpp)
target_link_libraries(test5 PUBLIC math_utils -lasan)
target_compile_options(test5 PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                      $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)
# ---------------build tutorial ---------------
add_subdirectory(tutorial)
#----------------build test target -----------------------
add_subdirectory(ut)

#--------- instal graph analysis toolbox--------------

set(CMAKE_PREFIX_PATH "$ENV{HOME}/local_package")
message(STATUS ${CMAKE_PREFIX_PATH})

# scan for all header files
file(GLOB_RECURSE graphics_lib_header_list ${CMAKE_CURRENT_SOURCE_DIR}/lib/graph_analysis_toolbox/*.h)
foreach(filename ${graphics_lib_header_list})
    message(STATUS "header file is: " ${filename})
endforeach()

# add lib config file
include(CMakePackageConfigHelpers)

#set_target_properties(mylib PROPERTIES PUBLIC_HEADER  "${CMAKE_CURRENT_SOURCE_DIR}/graph_analysis_toolbox/dijkstra/Dijkstra.h")
install(TARGETS GraphAnalysis
        EXPORT MyGraphAnalysis
        ARCHIVE DESTINATION lib)
install(FILES ${graphics_lib_header_list}
        DESTINATION include)
        #install (
#    FILES
#    ${CMAKE_CURRENT_BINARY_DIR}/${PackageName}Config.cmake
#    ${CMAKE_CURRENT_BINARY_DIR}/${PackageName}ConfigVersion.cmake
#    DESTINATION ${dest}
#)
#get_target_property(public_headers GraphAnalysis PUBLIC_HEADER)
#message(STATUS ${public_headers})