set(HEADER_MAIN_DIR ${PROJECT_SOURCE_DIR}/headers)
set(HEADER_PAGE_DIR ${PROJECT_SOURCE_DIR}/headers/pages)
set(HEADER_MPC_DIR ${PROJECT_SOURCE_DIR}/headers/pages/home_page_contents)
set(HEADER_RPC_DIR ${PROJECT_SOURCE_DIR}/headers/pages/home_page_contents/room_contents)
set(HEADER_MODELS_DIR ${PROJECT_SOURCE_DIR}/headers)

qt_add_library(RoomContents STATIC)

target_include_directories(RoomContents PUBLIC
    ${HEADER_MAIN_DIR}
    ${HEADER_PAGE_DIR}
    ${HEADER_MPC_DIR}
    ${HEADER_RPC_DIR}
)

target_link_libraries(RoomContents Qt6::Quick)
target_sources(RoomContents PRIVATE
    ${HEADER_RPC_DIR}/task_creation_form.h task_creation_form.cpp
    ${HEADER_RPC_DIR}/invitation_form.h invitation_form.cpp
    ${HEADER_RPC_DIR}/task_form.h task_form.cpp
    ${HEADER_RPC_DIR}/task_edit_form_page.h task_edit_form_page.cpp
    ${HEADER_RPC_DIR}/task_view_form_page.h task_view_form_page.cpp
)
