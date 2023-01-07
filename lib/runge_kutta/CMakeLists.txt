set(RUNGE_KUTTA runge_kutta)

add_library(${MATH_UTILS} STATIC "")
target_link_libraries(${MATH_UTILS} PUBLIC Eigen3::Eigen)
target_include_directories(${MATH_UTILS} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(${MATH_UTILS} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)
