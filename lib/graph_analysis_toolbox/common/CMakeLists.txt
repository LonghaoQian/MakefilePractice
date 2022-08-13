target_include_directories(${GRAPH_TARGET}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(common_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/GraphCommon.cpp
)

set(common_header_list
    ${CMAKE_CURRENT_SOURCE_DIR}/GraphCommon.h
)

target_sources(${GRAPH_TARGET}
                PRIVATE
                ${common_src_list}
                PUBLIC
                ${common_header_list})