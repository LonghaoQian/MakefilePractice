target_include_directories(${TGT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(parameter_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/parameter.cpp
)

target_sources(${TGT_NAME}
               PRIVATE
               ${parameter_src_list})