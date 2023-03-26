aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ misc_src)
set(LIB_LIST -lasan)
auto_target_add(misc_src LIB_LIST)