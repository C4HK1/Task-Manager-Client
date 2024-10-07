set(HEADER_MAIN_DIR ${PROJECT_SOURCE_DIR}/headers)
set(HEADER_PAGE_DIR ${PROJECT_SOURCE_DIR}/headers/pages)
set(HEADER_MPC_DIR ${PROJECT_SOURCE_DIR}/headers/pages/main_page_contents)

qt_add_library(MainPageContents STATIC)

target_include_directories(MainPageContents PUBLIC
    ${HEADER_MAIN_DIR}
    ${HEADER_PAGE_DIR}
    ${HEADER_MPC_DIR}
)

target_link_libraries(MainPageContents Qt6::Quick)
target_sources(MainPageContents PRIVATE
    ${HEADER_MPC_DIR}/list_rooms_page.h list_rooms_page.cpp
    ${HEADER_MPC_DIR}/profile_page.h profile_page.cpp
    ${HEADER_MPC_DIR}/room.h room.cpp
    ${HEADER_MPC_DIR}/room_creation_page.h room_creation_page.cpp
    ${HEADER_MPC_DIR}/rooms_page.h rooms_page.cpp
    ${HEADER_MPC_DIR}/settings_page.h settings_page.cpp
    ${HEADER_MPC_DIR}/widget_rooms_page.h widget_rooms_page.cpp
)
