set(SRC_FILES
    module_register.cpp
    test_module_0.cpp
    test_module_1.cpp
    test_module_2.cpp
    TopologyAnalysis.cpp
)
set(HEADER_FILES
    module_register.h
    test_module_0.h
    test_module_1.h
    test_module_2.h
    TopologyAnalysis.h
)
add_library(Topology STATIC ${HEADER_FILES} ${SRC_FILES})
target_link_libraries(Topology PUBLIC Eigen3::Eigen)
target_include_directories(Topology INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(Topology PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>
                       $<$<CXX_COMPILER_ID:GNU>:${GNU_FLAGS}>)