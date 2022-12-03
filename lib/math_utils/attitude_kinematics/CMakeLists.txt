target_include_directories(${MATH_UTILS}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(attitude_kinematics_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/attitude_kinematics.cpp
)

set(attitude_kinematics_header_list
    ${CMAKE_CURRENT_SOURCE_DIR}/attitude_kinematics.h
)

target_sources(${MATH_UTILS}
               PRIVATE
               ${attitude_kinematics_src_list}
               PUBLIC
               ${attitude_kinematics_header_list})