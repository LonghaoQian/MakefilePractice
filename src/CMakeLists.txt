#--------------- build target --------------------------

add_single_exc(TARGET tarjan_method_test
               SOURCE tarjan_method_test.cpp
               LIBRARIES ${LASAN};MultiThreadLib;GraphAnalysis
               COMPILE_OPTIONS ${COMPILE_FLAGS})

add_single_exc(TARGET johnson_curcit_test
               SOURCE johnson_curcit_test.cpp
               LIBRARIES ${LASAN};GraphAnalysis
               COMPILE_OPTIONS ${COMPILE_FLAGS})

add_single_exc(TARGET dijstra_test
               SOURCE dijstra_test.cpp
               LIBRARIES ${LASAN};GraphAnalysis
               COMPILE_OPTIONS ${COMPILE_FLAGS})

add_single_exc(TARGET singleton_test
               SOURCE singleton_test.cpp
               LIBRARIES -Wl,--whole-archive module_factory -Wl,--no-whole-archive ${LASAN}
               COMPILE_OPTIONS ${COMPILE_FLAGS})

add_single_exc(TARGET rotation_test
               SOURCE rotation_test.cpp
               LIBRARIES ${LASAN};math_utils
               COMPILE_OPTIONS ${COMPILE_FLAGS})

add_single_exc(TARGET compile_opt_test
               SOURCE compiler_optimization_test.cpp
               LIBRARIES ${LASAN}
               COMPILE_OPTIONS ${COMPILE_FLAGS})