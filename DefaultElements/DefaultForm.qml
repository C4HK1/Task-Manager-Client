import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts
import AppFrontend.LoginPage

Frame {
    id: form
    anchors.fill: parent

    property alias button_text: button.text
    property var option;

    Rectangle {
        width: 500
        height: 360
        color: "#303030"
        radius: 20
        anchors.centerIn: parent
        z: 3

        property bool focused: true

        GridLayout {
            width: 200
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            z: 4

            columns: 1

            DefaultButton {
                id: button
                Layout.fillWidth: true
                Layout.preferredHeight: 33

                onClicked: {
                    option()
                }
            }
        }

        MouseArea {
            anchors.fill: parent;
        }
    }

    MouseArea {
        anchors.fill: parent;

        onClicked: {
            form.destroy()
        }
    }
}
