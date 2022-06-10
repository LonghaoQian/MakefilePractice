set(SRC_FILES
    GraphCommon.cpp
    FindStrongComponents.cpp
#    BellmanFord.cpp
#    Dijkstra.cpp
#    FloydWarshall.cpp
    JohnsonCurcitAlg.cpp
#    JonhsonPathAlg.cpp
)
set(HEADER_FILES
    GraphCommon.h
    FindStrongComponents.h
#    BellmanFord.h
#    Dijkstra.h
#    FloydWarshall.h
    JohnsonCurcitAlg.h
#    JonhsonPathAlg.h
)
add_library(GraphAnalysis STATIC ${HEADER_FILES} ${SRC_FILES})
target_link_libraries(GraphAnalysis PUBLIC Eigen3::Eigen)
target_include_directories(GraphAnalysis INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(GraphAnalysis PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)