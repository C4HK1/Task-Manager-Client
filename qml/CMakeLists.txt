qt_add_library(Qml STATIC)
qt_add_qml_module(Qml
    URI "qml"
    VERSION 1.0
    QML_FILES
        Authorization.qml
        Invites.qml
        ListRooms.qml
        Loggout.qml
        MainWindow.qml
        MainWorkspace.qml
        Profile.qml
        ProfileDelete.qml
        ProfileRow.qml
        Registration.qml
        Room.qml
        RoomCreation.qml
        Settings.qml
        Task.qml
        TaskCreation.qml
        TaskCreationButton.qml
        Tasks.qml
        WidgetRooms.qml

    RESOURCE_PREFIX /qml
)

add_subdirectory(DefaultElements)
add_subdirectory(MainWorkspaceElements)
