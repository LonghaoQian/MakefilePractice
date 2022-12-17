target_include_directories(${TGT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(model_register_list
    ${CMAKE_CURRENT_SOURCE_DIR}/model_register.cpp
)

target_sources(${TGT_NAME}
               PRIVATE
               ${model_register_list})