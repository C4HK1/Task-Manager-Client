set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/headers/pages/main_page_contents)
qt_add_library(MainPageContents STATIC)

target_include_directories(MainPageContents PUBLIC ${INCLUDE_DIR} ${INCLUDE_DIR}/..)
target_link_libraries(MainPageContents Qt6::Quick)
target_sources(MainPageContents PRIVATE
    ${INCLUDE_DIR}/list_rooms_page.h list_rooms_page.cpp
    ${INCLUDE_DIR}/profile_page.h profile_page.cpp
    ${INCLUDE_DIR}/room.h room.cpp
    ${INCLUDE_DIR}/room_creation_page.h room_creation_page.cpp
    ${INCLUDE_DIR}/rooms_page.h rooms_page.cpp
    ${INCLUDE_DIR}/settings_page.h settings_page.cpp
    ${INCLUDE_DIR}/widget_rooms_page.h widget_rooms_page.cpp
)
