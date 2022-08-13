target_include_directories(${GRAPH_TARGET}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(floydwarshall_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/FloydWarshall.cpp
)

set(floydwarshall_header_list
    ${CMAKE_CURRENT_SOURCE_DIR}/FloydWarshall.h
)

target_sources(${GRAPH_TARGET}
                PRIVATE
                ${floydwarshall_src_list}
                PUBLIC
                ${floydwarshall_header_list})