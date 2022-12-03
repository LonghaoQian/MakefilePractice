set(LOG_UTILS log_utils)

add_library(${LOG_UTILS} STATIC "")
target_include_directories(${LOG_UTILS} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(${LOG_UTILS} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)