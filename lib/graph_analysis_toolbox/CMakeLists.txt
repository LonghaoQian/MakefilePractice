set(GRAPH_TARGET GraphAnalysis)

add_library(${GRAPH_TARGET} STATIC "")
target_link_libraries(${GRAPH_TARGET} PUBLIC Eigen3::Eigen)
target_include_directories(${GRAPH_TARGET} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(${GRAPH_TARGET} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)
add_subdirectory(dijkstra)
add_subdirectory(common)
add_subdirectory(johnson_find_curcits)
add_subdirectory(tarjan_scc_alg)