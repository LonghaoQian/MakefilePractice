aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ misc_src)
set(LIB_LIST ${LASAN})
batch_add_exc(
    SOURCE_LIST ${misc_src}
    LIBRARIES ${LIB_LIST}
    COMPILE_OPTIONS ${COMPILE_FLAGS}
)