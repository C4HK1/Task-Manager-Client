import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import MainWorkspaceElements
import AppFrontend

DefaultFrame {
    signal switchToRoomCreation()

    Flickable {
        objectName: qsTr("flickable")
        anchors.fill: parent
        leftMargin: 10
        rightMargin: 10
        topMargin: 10
        bottomMargin: 10

        contentHeight: room_container.height
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar {
            anchors.right: parent.right
        }

        GridLayout {
            objectName: qsTr("widget_container")
            id: room_container
            width: Math.min(parent.width, children.length * 270 + 20 * (children.length + 1))

            flow: GridLayout.LeftToRight

            columns: {
                for (var i = 1; i < 50; ++i) {
                    if (270 * i + 20 * (i + 1) > parent.width) {
                        i
                        break
                    }
                }
            }
        }
    }

    RoomCreationButton {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
    }
}
