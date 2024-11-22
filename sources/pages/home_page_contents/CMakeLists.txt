set(HEADER_MAIN_DIR ${PROJECT_SOURCE_DIR}/headers)
set(HEADER_DIR ${PROJECT_SOURCE_DIR}/headers/pages)
set(HEADER_MPC_DIR ${PROJECT_SOURCE_DIR}/headers/pages/home_page_contents)
set(HEADER_RPC_DIR ${PROJECT_SOURCE_DIR}/headers/pages/home_page_contents/room_contents)
set(HEADER_MODELS_DIR ${PROJECT_SOURCE_DIR}/headers)

qt_add_library(HomePageContents STATIC)


find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED IMPORTED_TARGET glib-2.0)
pkg_search_module(RDKAFKA++ REQUIRED IMPORTED_TARGET rdkafka++)
pkg_search_module(RDKAFKA REQUIRED IMPORTED_TARGET rdkafka)


add_subdirectory(room_contents)
target_include_directories(HomePageContents PUBLIC
    ${HEADER_MAIN_DIR}
    ${HEADER_DIR}
    ${HEADER_MPC_DIR}
    ${HEADER_RPC_DIR}
)

target_link_libraries(HomePageContents Qt6::Quick RoomContents PkgConfig::GLIB PkgConfig::RDKAFKA++ PkgConfig::RDKAFKA)
target_sources(HomePageContents PRIVATE
    ${HEADER_MPC_DIR}/list_rooms.h list_rooms.cpp
    ${HEADER_MPC_DIR}/profile.h profile.cpp
    ${HEADER_MPC_DIR}/room_creation.h room_creation.cpp
    ${HEADER_MPC_DIR}/rooms_list.h rooms_list.cpp
    ${HEADER_MPC_DIR}/settings.h settings.cpp
    ${HEADER_MPC_DIR}/widget_rooms.h widget_rooms.cpp
    ${HEADER_MPC_DIR}/room.h room.cpp
    ${HEADER_MPC_DIR}/tasks_list.h tasks_list.cpp
    ${HEADER_MPC_DIR}/all_tasks.h all_tasks.cpp
    ${HEADER_MPC_DIR}/assigned_tasks.h assigned_tasks.cpp
    ${HEADER_MPC_DIR}/reviewed_tasks.h reviewed_tasks.cpp
    ${HEADER_MPC_DIR}/invites_list.h invites_list.cpp
    ${HEADER_MPC_DIR}/all_invites.h all_invites.cpp
    ${HEADER_MPC_DIR}/sended_invites.h sended_invites.cpp
    ${HEADER_MPC_DIR}/received_invites.h received_invites.cpp
    ${HEADER_MPC_DIR}/loggout_form.h loggout_form.cpp
    ${HEADER_MPC_DIR}/profile_delete_form.h profile_delete_form.cpp
)
