target_include_directories(${UT_TARGET}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(ut_attitude_kinematics_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/ut_attitude_kinematics.cpp
)

target_sources(${UT_TARGET}
               PRIVATE
               ${ut_attitude_kinematics_src_list})