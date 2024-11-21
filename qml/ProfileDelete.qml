import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements
import qml.DefaultElements.Fonts

DefaultForm {
    property var option;

    signal profileDelete()

    GridLayout {
        width: 200
        parent: container
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        columns: 1

        DefaultButton {
            id: button
            Layout.fillWidth: true
            Layout.preferredHeight: 33
            text: "delete profile"

            onClicked: {
                profileDelete()
            }
        }
    }
}
