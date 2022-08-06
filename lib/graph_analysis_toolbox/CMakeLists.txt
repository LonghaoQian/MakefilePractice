set(GRAPH_TARGET GraphAnalysis)

set(GRAPH_ANALYSIS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/common/GraphCommon.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/dijkstra/Dijkstra.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/tarjan_scc_alg/FindStrongComponents.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/johnson_find_curcits/JohnsonCurcitAlg.cpp"
)
set(GRAPH_ANALYSIS_DIR
    "${CMAKE_CURRENT_LIST_DIR}/common"
    "${CMAKE_CURRENT_LIST_DIR}/dijkstra"
    "${CMAKE_CURRENT_LIST_DIR}/tarjan_scc_alg"
    "${CMAKE_CURRENT_LIST_DIR}/johnson_find_curcits"
)

add_library(${GRAPH_TARGET} STATIC ${GRAPH_ANALYSIS_SRC})
target_link_libraries(${GRAPH_TARGET} PUBLIC Eigen3::Eigen)
target_include_directories(${GRAPH_TARGET} PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${GRAPH_ANALYSIS_DIR})
target_compile_options(${GRAPH_TARGET} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)