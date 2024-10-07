import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import MainWorkspaceElements

DefaultFrame {
    Flickable {
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
            id: room_container
            width: parent.width

            flow: GridLayout.LeftToRight

            columns: {
                for (var i = 1; i < 50; ++i) {
                    if (250 * i + 20 * (i + 1) > parent.width) {
                        i
                        break
                    }
                }
            }

            RoomWidget {
                room_name: "Qt Task Organizer"
                owner_name: "C4HK1, gerarte04"
            }
            RoomWidget {
                room_name: "ML engineering"
                owner_name: "Elon Musk"
            }
            RoomWidget {
                room_name: "My Project"
                owner_name: "Lil Cheecha"
            }
            RoomWidget {}
            RoomWidget {}
            RoomWidget {}
            RoomWidget {}
            RoomWidget {}
        }
    }

    RoomCreationButton {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
    }
}
