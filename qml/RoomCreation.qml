import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import AppFrontend

Flickable {
    anchors.fill: parent
    anchors.topMargin: 40
    anchors.leftMargin: 40

    contentHeight: room_settings.height
    boundsBehavior: Flickable.StopAtBounds

    ScrollBar.vertical: ScrollBar {
        anchors.right: parent.right
    }

    GridLayout {
        id: room_settings

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
            id: room_name
        }

        DefaultButton {
            Layout.columnSpan: 2
            text: "Create"
            onClicked: { NetworkManager.sendRoomCreationRequest(room_name.text) }
        }
    }
}
