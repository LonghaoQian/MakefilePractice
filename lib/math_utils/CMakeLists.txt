set(MATH_UTILS math_utils)

add_library(${MATH_UTILS} STATIC "")
target_link_libraries(${MATH_UTILS} PUBLIC Eigen3::Eigen)
target_include_directories(${MATH_UTILS} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(${MATH_UTILS} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)
add_subdirectory(utils)
add_subdirectory(attitude_kinematics)
add_subdirectory(lookup_table)
add_subdirectory(optimization)