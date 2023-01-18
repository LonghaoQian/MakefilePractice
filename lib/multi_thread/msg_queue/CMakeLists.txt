target_include_directories(${THREAD_POOL}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(msg_queue_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/msg_queue.cpp
)

target_sources(${THREAD_POOL}
               PRIVATE
               ${msg_queue_src_list})