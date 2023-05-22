target_include_directories(${UT_TARGET}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(ut_file_io_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/ut_file_io.cpp
)

target_sources(${UT_TARGET} PRIVATE ${ut_file_io_src_list})