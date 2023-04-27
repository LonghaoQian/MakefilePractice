aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ iterator_src)
set(LIB_LIST -lasan)
auto_target_add(iterator_src LIB_LIST)