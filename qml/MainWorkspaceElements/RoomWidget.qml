import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    Layout.margins: 10
    Layout.fillWidth: true
    Layout.maximumWidth: 270
    height: 170
    radius: 20

    color: "#404040"

    property alias roomName: roomName.text
    property alias roomCreatorName: roomCreatorName.text
    property int roomCreatorID

    signal switchToRoom(int roomCreatorID, string roomName)

    Text {
        id: roomName
        objectName: qsTr("roomName")
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 15
        anchors.topMargin: 15
        color: "#FFFFFF"
        font.pixelSize: 18
        font.bold: true
        width: parent.width - anchors.leftMargin * 2
        wrapMode: Text.WordWrap
        maximumLineCount: 2
        elide: Text.ElideRight
    }

    Text {
        id: roomCreatorName
        objectName: qsTr("roomCreatorName")
        anchors.left: parent.left
        anchors.top: roomName.bottom
        anchors.leftMargin: 15
        anchors.topMargin: 10
        anchors.margins: 15
        color: "#FFFFFF"
        font.pixelSize: 16
        width: parent.width - anchors.leftMargin * 2
        wrapMode: Text.WordWrap
        maximumLineCount: 2
        elide: Text.ElideRight
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            parent.color = "#505050"
        }

        onExited: {
            parent.color = "#404040"
        }

        onClicked: {
            switchToRoom(roomCreatorID, roomName.text);
        }
    }
}
