target_include_directories(${MATH_UTILS}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(math_utils_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/math_utils.cpp
)

set(math_utils_header_list
    ${CMAKE_CURRENT_SOURCE_DIR}/math_utils.h
)

target_sources(${MATH_UTILS}
               PRIVATE
               ${math_utils_src_list}
               PUBLIC
               ${math_utils_header_list})