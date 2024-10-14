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
        RoomCreationButton.qml

    RESOURCE_PREFIX /MainWorkspaceElements
    QML_FILES TaskListItem.qml
)
