target_include_directories(${GRAPH_TARGET}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(dijkstra_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/Dijkstra.cpp
)

set(dijkstra_header_list
    ${CMAKE_CURRENT_SOURCE_DIR}/Dijkstra.h
)

target_sources(${GRAPH_TARGET}
                PRIVATE
                ${dijkstra_src_list}
                PUBLIC
                ${dijkstra_header_list})