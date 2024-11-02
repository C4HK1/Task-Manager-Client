set(HEADER_MAIN_DIR ${PROJECT_SOURCE_DIR}/headers)
set(HEADER_PAGE_DIR ${PROJECT_SOURCE_DIR}/headers/pages)
set(HEADER_MPC_DIR ${PROJECT_SOURCE_DIR}/headers/pages/home_page_contents)
set(HEADER_RPC_DIR ${PROJECT_SOURCE_DIR}/headers/pages/home_page_contents/room_contents)
set(HEADER_MODELS_DIR ${PROJECT_SOURCE_DIR}/headers)

qt_add_library(MainApplication STATIC)

add_subdirectory(pages)
add_subdirectory(models)
target_include_directories(MainApplication PUBLIC
    ${HEADER_MAIN_DIR}
    ${HEADER_PAGE_DIR}
    ${HEADER_MPC_DIR}
    ${HEADER_RPC_DIR}
    ${HEADER_MODELS_DIR}
)
target_link_libraries(MainApplication Qt6::Quick Pages Models)
target_sources(MainApplication PRIVATE
    ${HEADER_MAIN_DIR}/main_application.h main_application.cpp
    ${HEADER_MAIN_DIR}/network_manager.h network_manager.cpp
    ${HEADER_MAIN_DIR}/models.h
    ${HEADER_MODELS_DIR}
)
