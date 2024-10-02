import QtQuick
import AppFrontend

Rectangle {
    width: 35
    height: 35
    color: "#404040"
    radius: 5
    border.width: 1
    border.color: "#202020"

    property var onClickFunction: function() { MainApplication.switchToRoomCreation(); }

    id: id

    Text {
        id: name
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: "#FFFFFF"
        font.pixelSize: 24
        text: qsTr("+")
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onClicked: onClickFunction()

        onEntered: {
            parent.color = "#505050"
        }

        onExited: {
            parent.color = "#404040"
        }
    }
}
