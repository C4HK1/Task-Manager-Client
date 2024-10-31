import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    Layout.fillWidth: true
    Layout.leftMargin: -1
    Layout.rightMargin: -1
    height: 50

    color: "#242424"
    border.width: 2
    border.color: "#303030"

    property alias taskName: taskName.text
    property alias roomName: roomName.text
    property int roomCreatorID

    signal openRoom(int roomCreatorID, string roomName)

    Text {
        id: taskName
        objectName: qsTr("taskName")
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 20
        color: "white"
        font.pixelSize: 14
        font.bold: true
        width: 200
        elide: Text.ElideRight
    }

    Text {
        id: roomName
        objectName: qsTr("roomName")
        anchors.left: taskName.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 15
        color: "white"
        font.pixelSize: 14
        width: 150
        elide: Text.ElideRight
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onClicked: openRoom(roomCreatorID, roomName.text)

        onEntered: {
            parent.border.color = "#404040"
            parent.border.width = 5
            parent.z = 2
        }

        onExited: {
            parent.border.color = "#303030"
            parent.border.width = 2
            parent.z = 0
        }
    }
}
