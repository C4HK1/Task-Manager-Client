set(HEADER_MODELS_DIR ${PROJECT_SOURCE_DIR}/headers)

qt_add_library(Models STATIC)

target_include_directories(Models PUBLIC
    ${HEADER_MODELS_DIR}
)
target_link_libraries(Models Qt6::Quick)
target_sources(Models PRIVATE
    ${HEADER_MODELS_DIR}/models/profile.h profile.cpp
    ${HEADER_MODELS_DIR}/models/profiles.h profiles.cpp
    ${HEADER_MODELS_DIR}/models/room.h room.cpp
    ${HEADER_MODELS_DIR}/models/rooms.h rooms.cpp
    ${HEADER_MODELS_DIR}/models/task.h task.cpp
    ${HEADER_MODELS_DIR}/models/tasks.h tasks.cpp
    ${HEADER_MODELS_DIR}/models/config.h config.cpp
    ${HEADER_MODELS_DIR}/models/server_status.h server_status.cpp
)


