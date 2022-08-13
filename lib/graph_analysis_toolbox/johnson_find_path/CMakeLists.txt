target_include_directories(${GRAPH_TARGET}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(johnson_path_alg_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/JohnsonPathAlg.cpp
)

set(johnson_path_alg_header_list
    ${CMAKE_CURRENT_SOURCE_DIR}/JohnsonPathAlg.h
)

target_sources(${GRAPH_TARGET}
                PRIVATE
                ${johnson_path_alg_src_list}
                PUBLIC
                ${johnson_path_alg_header_list})