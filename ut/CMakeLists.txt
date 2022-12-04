set(UT_TARGET ut_test1)

# directory to gtest library
set(GTEST_HEADER_DIR "../google_test/debug/include")
set(GTEST_LIB_DIR "../google_test/debug/lib")

# directories of source files to be tested
set(ut_math_utils_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/math_utils/attitude_kinematics
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/math_utils/utils
)

set(ut_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/ut_example.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ut_main.cpp
)

set(ut_header_list
    ${CMAKE_CURRENT_SOURCE_DIR}/${GTEST_HEADER_DIR}
)

set(ut_gtestlib_dir
    ${CMAKE_CURRENT_SOURCE_DIR}/${GTEST_LIB_DIR}
)

add_executable(${UT_TARGET} ${ut_src_list})
# when using gtest, pthread lib must be linked as well
target_link_libraries(${UT_TARGET} PUBLIC Eigen3::Eigen -lasan gtestd gtest_maind pthread --coverage)
target_link_directories(${UT_TARGET} PUBLIC ${ut_gtestlib_dir})

target_include_directories(${UT_TARGET} 
                            PUBLIC
                            ${CMAKE_CURRENT_LIST_DIR}
                            ${ut_header_list}
                            ${ut_math_utils_src_list})

target_compile_options(${UT_TARGET}
                        PRIVATE
                        $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>$<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>
                        --coverage
)

add_subdirectory(ut_lib)