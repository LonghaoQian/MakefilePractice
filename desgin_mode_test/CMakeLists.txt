set(TGT_NAME module_factory)

add_library(${TGT_NAME} STATIC "")
target_link_libraries(${TGT_NAME} PUBLIC Eigen3::Eigen)
target_include_directories(${TGT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(${TGT_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)

add_subdirectory(model_register)
add_subdirectory(modules)
add_subdirectory(solver)
add_subdirectory(model_manager)