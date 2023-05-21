aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ multi_threading_src)
set(LIB_LIST ${LASAN};-lpthread;MultiThreadLib)
batch_add_exc(
    SOURCE_LIST ${multi_threading_src}
    LIBRARIES ${LIB_LIST}
    COMPILE_OPTIONS ${COMPILE_FLAGS}
)