set(HEADER_MAIN_DIR ${PROJECT_SOURCE_DIR}/headers)
set(HEADER_PAGE_DIR ${PROJECT_SOURCE_DIR}/headers/pages)
set(HEADER_MPC_DIR ${PROJECT_SOURCE_DIR}/headers/pages/main_page_contents)
qt_add_library(Pages STATIC)

add_subdirectory(main_page_contents)
target_include_directories(Pages PUBLIC
    ${HEADER_MAIN_DIR}
    ${HEADER_PAGE_DIR}
    ${HEADER_MPC_DIR}
)
target_link_libraries(Pages Qt6::Quick MainPageContents)
target_sources(Pages PRIVATE
    ${HEADER_PAGE_DIR}/authorization_page.h authorization_page.cpp
    ${HEADER_PAGE_DIR}/base_page.h base_page.cpp
    ${HEADER_PAGE_DIR}/main_page.h main_page.cpp
    ${HEADER_PAGE_DIR}/registration_page.h registration_page.cpp
)
