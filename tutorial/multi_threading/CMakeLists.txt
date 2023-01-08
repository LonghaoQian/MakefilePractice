aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ multi_threading_src)
set(LIB_LIST -lasan;-lpthread)
auto_target_add(multi_threading_src LIB_LIST)