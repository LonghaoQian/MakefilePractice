target_include_directories(${GRAPH_TARGET}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(bellmanford_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/BellmanFord.cpp
)

set(bellmanford_header_list
    ${CMAKE_CURRENT_SOURCE_DIR}/BellmanFord.h
)

target_sources(${GRAPH_TARGET}
                PRIVATE
                ${bellmanford_src_list}
                PUBLIC
                ${bellmanford_header_list})