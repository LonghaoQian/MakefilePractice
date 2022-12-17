target_include_directories(${TGT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(module_a_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/module_a_register.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/module_a.cpp
)

target_sources(${TGT_NAME}
               PRIVATE
               ${module_a_src_list})