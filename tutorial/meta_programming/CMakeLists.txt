aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ meta_programming_src)
set(LIB_LIST -lasan)
auto_target_add(meta_programming_src LIB_LIST)