target_include_directories(${TGT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(solver_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/solver.cpp
)

target_sources(${TGT_NAME}
               PRIVATE
               ${solver_src_list})