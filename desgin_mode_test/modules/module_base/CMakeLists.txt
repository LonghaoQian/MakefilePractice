target_include_directories(${TGT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(module_base_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/module_base.cpp
)

target_sources(${TGT_NAME}
               PRIVATE
               ${module_base_src_list})