# define a pure interface class with only header files
set(MULTI_THREAD MultiThreadLib)
add_library(${MULTI_THREAD} INTERFACE)
target_include_directories(${MULTI_THREAD} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(msg_queue)
add_subdirectory(thread_pool)