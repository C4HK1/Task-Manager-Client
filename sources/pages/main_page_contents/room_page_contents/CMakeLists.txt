set(HEADER_MAIN_DIR ${PROJECT_SOURCE_DIR}/headers)
set(HEADER_PAGE_DIR ${PROJECT_SOURCE_DIR}/headers/pages)
set(HEADER_MPC_DIR ${PROJECT_SOURCE_DIR}/headers/pages/main_page_contents)
set(HEADER_RPC_DIR ${PROJECT_SOURCE_DIR}/headers/pages/main_page_contents/room_page_contents)

qt_add_library(RoomPageContents STATIC)

target_include_directories(RoomPageContents PUBLIC
    ${HEADER_MAIN_DIR}
    ${HEADER_PAGE_DIR}
    ${HEADER_MPC_DIR}
    ${HEADER_RPC_DIR}
)

target_link_libraries(RoomPageContents Qt6::Quick)
target_sources(RoomPageContents PRIVATE
    ${HEADER_RPC_DIR}/task_creation_form.h task_creation_form.cpp
)
