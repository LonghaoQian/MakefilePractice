target_include_directories(${TGT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(model_manager_src_list
    ${CMAKE_CURRENT_SOURCE_DIR}/model_manager.cpp
)

target_sources(${TGT_NAME}
               PRIVATE
               ${model_manager_src_list})