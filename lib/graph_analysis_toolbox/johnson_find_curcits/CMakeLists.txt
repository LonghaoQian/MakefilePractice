target_include_directories(${GRAPH_TARGET}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(johnson_find_path_curcits_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/JohnsonCurcitAlg.cpp
)

set(johnson_find_path_curcits_header_list
    ${CMAKE_CURRENT_SOURCE_DIR}/JohnsonCurcitAlg.h
)

target_sources(${GRAPH_TARGET}
                PRIVATE
                ${johnson_find_path_curcits_src_list}
                PUBLIC
                ${johnson_find_path_curcits_header_list})