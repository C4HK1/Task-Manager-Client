set(HEADER_MAIN_DIR ${PROJECT_SOURCE_DIR}/headers)
set(HEADER_DIR ${PROJECT_SOURCE_DIR}/headers/pages)
set(HEADER_MPC_DIR ${PROJECT_SOURCE_DIR}/headers/pages/home_page_contents)
set(HEADER_RPC_DIR ${PROJECT_SOURCE_DIR}/headers/pages/home_page_contents/room_contents)
set(HEADER_MODELS_DIR ${PROJECT_SOURCE_DIR}/headers)

qt_add_library(Pages STATIC)

add_subdirectory(home_page_contents)
target_include_directories(Pages PUBLIC
    ${HEADER_MAIN_DIR}
    ${HEADER_DIR}
    ${HEADER_MPC_DIR}
    ${HEADER_RPC_DIR}
)
target_link_libraries(Pages Qt6::Quick HomePageContents)
target_sources(Pages PRIVATE
    ${HEADER_DIR}/loggining_page.h loggining_page.cpp
    ${HEADER_DIR}/base_element.h base_element.cpp
    ${HEADER_DIR}/home_page.h home_page.cpp
    ${HEADER_DIR}/registration_page.h registration_page.cpp
)
