import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts
import MainWorkspaceElements

DefaultFrame {
    Rectangle {
        id: sidebar_bg
        anchors.left: parent.left
        anchors.top: topbar_bg.bottom
        anchors.bottom: parent.bottom
        width: 70

        color: "#303030"
    }

    Column {
        anchors.fill: sidebar_bg

        SidebarButton {
            name: "R"
        }

        SidebarButton {
            name: "T"
        }

        SidebarButton {
            name: "S"
        }
    }

    Rectangle {
        id: topbar_bg
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        height: 30

        color: "#303030"
    }

    Flickable {
        anchors.left: sidebar_bg.right
        anchors.top: topbar_bg.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom

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
}
