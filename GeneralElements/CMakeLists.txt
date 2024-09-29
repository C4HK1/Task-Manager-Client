qt_add_library(GeneralElements STATIC)
qt_add_qml_module(GeneralElements
    URI "GeneralElements"
    VERSION 1.0
    QML_FILES
        SidebarButton.qml
        ProfileTools.qml
        TopbarRoomsViewButton.qml

    RESOURCE_PREFIX /GeneralElements
)
