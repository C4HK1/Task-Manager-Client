qt_add_library(MainWorkspaceElements STATIC)
qt_add_qml_module(MainWorkspaceElements
    URI "qml.MainWorkspaceElements"
    VERSION 1.0
    QML_FILES
        RoomWidget.qml
        RoomListItem.qml
        SidebarButton.qml
        TopbarRoomsViewButton.qml
        RoomCreationButton.qml
        InviteForm.qml
        TaskListItem.qml
        ReceivedInviteListItem.qml
        SendedInviteListItem.qml
        TaskTools.qml
        InviteTools.qml
        ProfileTools.qml
        PageSwitchingButton.qml
        TaskForm.qml
    RESOURCE_PREFIX /
)
