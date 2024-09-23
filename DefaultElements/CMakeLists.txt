qt_add_library(DefaultElements STATIC)
qt_add_qml_module(DefaultElements
    URI "DefaultElements"
    VERSION 1.0
    QML_FILES
        DefaultButton.qml
        DefaultTextField.qml
        DefaultFrame.qml
    RESOURCE_PREFIX /DefaultElements
)

add_subdirectory(Fonts)
