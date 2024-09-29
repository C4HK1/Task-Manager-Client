qt_add_library(MainWorkspaceElements STATIC)
qt_add_qml_module(MainWorkspaceElements
    URI "MainWorkspaceElements"
    VERSION 1.0
    QML_FILES
        RoomWidget.qml
    RESOURCE_PREFIX /MainWorkspaceElements
)


