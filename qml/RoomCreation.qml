import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements

Flickable {
    function roomCreationFailed() {
        console.log("room creation failed")
    }

    signal createRoom(string roomName, string description)

    anchors.fill: parent
    anchors.topMargin: 40
    anchors.leftMargin: 40

    contentHeight: roomSettings.height
    boundsBehavior: Flickable.StopAtBounds

    ScrollBar.vertical: ScrollBar {
        anchors.right: parent.right
    }

    GridLayout {
        id: roomSettings

        flow: GridLayout.LeftToRight
        columns: 2
        rowSpacing: 30
        columnSpacing: 20

        Text {
            Layout.columnSpan: 2
            font.bold: true
            font.pixelSize: 36
            text: "Create room"
            color: "#FFFFFF"
        }

        Text {
            font.pixelSize: 18
            text: "Room name"
            color: "#FFFFFF"
        }

        DefaultTextField {
            id: roomName
        }

        Text {
            font.pixelSize: 18
            text: "Room description"
            color: "#FFFFFF"
        }

        DefaultTextField {
            id: roomDescription
        }

        DefaultButton {
            Layout.columnSpan: 2
            text: "Create"
            onClicked: { createRoom(roomName.text, roomDescription.text) }
        }
    }
}
