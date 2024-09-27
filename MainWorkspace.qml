import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts
import MainWorkspaceElements

DefaultFrame {
    id: root

    function createImageObject(str, root) {
        var component = Qt.createComponent(str)
        if (component.status === Component.Ready || component.status === Component.Error)
        {
            return finishCreation(component, root)
        } else {
            component.statusChanged.connect(finishCreation)
        }
    }
    function finishCreation(component, root) {
        if (component.status === Component.Ready) {
            return component.createObject(root)
        } else if (component.status === Component.Error) {
            console.log("Error loading component:", component.errorString())
        }
    }

    property var profile_tools;
    property var tables;

    Rectangle {

        property int slimToolBarWidth: 70
        property int toolBarWidth: 160

        id: sidebar_bg
        anchors.left: parent.left
        anchors.top: topbar_bg.bottom
        anchors.bottom: parent.bottom
        width: slimToolBarWidth
        z: 1

        color: "#303030"

        Flickable {
            id: tool_bar
            anchors.fill: parent
            z: 2

            contentHeight: room_container.height
            boundsBehavior: Flickable.StopAtBounds

            ScrollBar.vertical: ScrollBar {
                anchors.right: parent.right
            }
            GridLayout {
                width: parent.width
                columns: 1

                SidebarButton {
                    name: "R"
                    font_size: 36
                }

                SidebarButton {
                    name: "T"
                    font_size: 36
                }

                Rectangle {
                    anchors.left: parent.left
                    width: parent.width

                    SidebarButton {
                        name: "PT"
                        id: tool_bar_profile
                        font_size: 36
                        onClickFunction: function() {
                            if (profile_tools === undefined) {
                                profile_tools = root.createImageObject("MainWorkspaceElements/ProfileTools.qml", profile_tool_root)
                            }
                        }
                    }

                    Rectangle {
                        id: profile_tool_root
                        anchors.top: tool_bar_profile.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: sidebar_bg.bottom
                    }
                }
            }
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                parent.width = parent.toolBarWidth
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        z: 0

        onEntered: {
            if (profile_tools !== undefined) {
                profile_tools.destroy()
                profile_tools = undefined
            }
            sidebar_bg.width = sidebar_bg.slimToolBarWidth
        }
    }

    Rectangle {
        id: topbar_bg
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        height: 30
        z: -1

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
