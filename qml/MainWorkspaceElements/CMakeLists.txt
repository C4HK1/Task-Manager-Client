qt_add_library(MainWorkspaceElements STATIC)
qt_add_qml_module(MainWorkspaceElements
    URI "MainWorkspaceElements"
    VERSION 1.0
    QML_FILES
        RoomWidget.qml
        RoomListItem.qml
	SidebarButton.qml
        ProfileTools.qml
        TopbarRoomsViewButton.qml
        Tasks.qml
        Task.qml
        RoomCreationButton.qml
        TaskCreationButton.qml

    RESOURCE_PREFIX /MainWorkspaceElements
)
