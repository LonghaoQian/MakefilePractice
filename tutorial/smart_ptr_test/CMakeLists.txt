aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ smart_ptr_src)
set(LIB_LIST -lasan)
auto_target_add(smart_ptr_src LIB_LIST)