set_source_files_properties(DefaultFont.qml PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)

qt_add_library(Fonts STATIC)
qt_add_qml_module(Fonts
    URI "DefaultElements.Fonts"
    VERSION 1.0
    QML_FILES
        DefaultFont.qml
    RESOURCE_PREFIX /DefaultElements/Fonts
)
