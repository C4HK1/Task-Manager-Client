import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts
import MainWorkspaceElements

DefaultFrame {
    signal switchToRoomCreation()

    Rectangle {
        id: infoTopBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 3
        anchors.leftMargin: 3
        height: 30

        color: "#303030"

        Text {
            id: roomName
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 17
            color: "white"
            font.pixelSize: 16
            font.bold: true
            width: 200
            text: qsTr("Room name")
        }

        Text {
            anchors.left: roomName.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 13
            color: "white"
            font.pixelSize: 16
            font.bold: true
            width: 150
            text: qsTr("Owner name")
        }
    }

    Flickable {
        objectName: qsTr("flickable")
        anchors.top: infoTopBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 3

        contentHeight: roomContainer.height
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar {
            anchors.right: parent.right
        }

        GridLayout {
            id: roomContainer
            objectName: qsTr("listContainer")
            width: parent.width
            rowSpacing: -2

            flow: GridLayout.LeftToRight
            columns: 1
        }
    }

    RoomCreationButton {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
    }
}
