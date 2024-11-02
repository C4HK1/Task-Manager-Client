import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts

Frame {
    id: form
    anchors.fill: parent
    z: 2

    property var option;

    signal loggout()
    signal closeLoggoutForm()

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
                text: "loggout"

                onClicked: {
                    loggout()
                }
            }
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            closeLoggoutForm()
        }
    }
}
