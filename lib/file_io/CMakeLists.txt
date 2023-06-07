set(FILE_IO file_io)
add_library(${FILE_IO} INTERFACE)
target_include_directories(${FILE_IO} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})