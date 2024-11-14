qt_add_library(DefaultElements STATIC)
qt_add_qml_module(DefaultElements
    URI "qml.DefaultElements"
    VERSION 1.0
    QML_FILES
        DefaultButton.qml
        DefaultTextField.qml
        DefaultFrame.qml
        DefaultForm.qml
    RESOURCE_PREFIX /qml/DefaultElements
)

add_subdirectory(Fonts)
