set(THREAD_POOL thread_pool)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ thread_pool_src_list)
add_library(${THREAD_POOL} STATIC ${thread_pool_src_list})
target_include_directories(${THREAD_POOL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${THREAD_POOL} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(${THREAD_POOL} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)