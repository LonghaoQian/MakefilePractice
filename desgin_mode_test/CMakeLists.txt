set(TGT_NAME module_factory)

#set(SRC_FILES
#    module_register.cpp
#    test_module_0.cpp
#    test_module_1.cpp
#    test_module_2.cpp
#)
#set(HEADER_FILES
#    module_register.h
#    test_module_0.h
#    test_module_1.h
#    test_module_2.h
#)
add_library(${TGT_NAME} STATIC "")
target_link_libraries(${TGT_NAME} PUBLIC Eigen3::Eigen)
target_include_directories(${TGT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(${TGT_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)

add_subdirectory(model_register)
add_subdirectory(modules)
add_subdirectory(solver)