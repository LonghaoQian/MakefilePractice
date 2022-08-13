target_include_directories(${GRAPH_TARGET}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(tarjan_scc_alg_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/FindStrongComponents.cpp
)

set(tarjan_scc_alg_header_list
    ${CMAKE_CURRENT_SOURCE_DIR}/FindStrongComponents.h
)

target_sources(${GRAPH_TARGET}
                PRIVATE
                ${tarjan_scc_alg_src_list}
                PUBLIC
                ${tarjan_scc_alg_header_list})