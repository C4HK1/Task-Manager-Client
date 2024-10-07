set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/headers/pages)
qt_add_library(Pages STATIC)

add_subdirectory(main_page_contents)
target_include_directories(Pages PUBLIC ${INDLUDE_DIR} ${INCLUDE_DIR}/..)
target_link_libraries(Pages Qt6::Quick MainPageContents)
target_sources(Pages PRIVATE
    ${INCLUDE_DIR}/authorization_page.h authorization_page.cpp
    ${INCLUDE_DIR}/base_page.h base_page.cpp
    ${INCLUDE_DIR}/main_page.h main_page.cpp
    ${INCLUDE_DIR}/registration_page.h registration_page.cpp
)
