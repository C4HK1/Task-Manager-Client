import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements
import qml.DefaultElements.Fonts

Frame {
    id: form
    anchors.fill: parent
    z: 2

    property var option;

    signal profileDelete()
    signal closeProfileDeleteForm()

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

    MouseArea {
        anchors.fill: parent

        onClicked: {
            closeProfileDeleteForm()
        }
    }
}
