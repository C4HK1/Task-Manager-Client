import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts
import MainWorkspaceElements
import GeneralElements
import AppFrontend.LoginPage

DefaultFrame {
    id: root

    function createImageObject(str, root, params) {
        var component = Qt.createComponent(str)
        if (component.status === Component.Ready || component.status === Component.Error)
        {
            return finishCreation(component, root, params)
        } else {
            component.statusChanged.connect(finishCreation)
        }
    }
    function finishCreation(component, root, params) {
        if (component.status === Component.Ready) {
            return component.createObject(root, params)
        } else if (component.status === Component.Error) {
            console.log("Error loading component:", component.errorString())
        }
    }

    property var profile_tools;
    property bool widgetRoomsView: true

    Rectangle {
        property int slimToolBarWidth: 70
        property int toolBarWidth: 160

        id: sidebar_bg

        anchors.top: topbar_bg.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: slimToolBarWidth
        z: 1

        color: "#303030"

        Flickable {
            id: tool_bar
            anchors.fill: parent
            z: 2

            contentHeight: sidebar_container.height
            boundsBehavior: Flickable.StopAtBounds

            ScrollBar.vertical: ScrollBar {
                anchors.right: parent.right
            }

            GridLayout {
                id: sidebar_container
                width: parent.width
                columns: 1

                SidebarButton {
                    name: "R"
                    font_size: 36

                    onClickFunction: function() {
                        if(widgetRoomsView){
                            MainApplication.switchToWidgetRooms()
                        } else {
                            MainApplication.switchToListRooms()
                        }
                    }
                }

                SidebarButton {
                    name: "T"
                    font_size: 36
                }

                Rectangle {
                    width: parent.width

                    SidebarButton {
                        name: "PT"
                        id: tool_bar_profile
                        font_size: 36
                        onClickFunction: function() {
                            if (profile_tools === undefined) {
                                profile_tools = root.createImageObject("GeneralElements/ProfileTools.qml", profile_tool_root)
                            }
                        }
                    }

                    Rectangle {
                        id: profile_tool_root
                        anchors.top: tool_bar_profile.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                    }
                }
            }
        }

        MouseArea {
            anchors.fill: sidebar_bg
            hoverEnabled: true

            onEntered: {
                parent.width = parent.toolBarWidth
            }
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

        TopbarRoomsViewButton {
            id: widget_view_button
            name: "W"
            anchors.top: parent.top
            anchors.right: parent.right
            z: 1

            onClickFunction: function() {
                widgetRoomsView = true
                MainApplication.switchToWidgetRooms()
            }
        }

        TopbarRoomsViewButton {
            id: list_view_button
            name: "L"
            anchors.top: parent.top
            anchors.right: widget_view_button.left
            z: 1

            onClickFunction: function() {
                widgetRoomsView = false
                MainApplication.switchToListRooms()
            }
        }

        MouseArea {
            z: 0
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                if (profile_tools !== undefined) {
                    profile_tools.destroy()
                    profile_tools = undefined
                }
                sidebar_bg.width = sidebar_bg.slimToolBarWidth
            }
        }
    }

    Frame {
        objectName: qsTr("workspace")
        anchors.top: topbar_bg.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: parent.width - sidebar_bg.slimToolBarWidth
        padding: 0

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                if (profile_tools !== undefined) {
                    profile_tools.destroy()
                    profile_tools = undefined
                }
                sidebar_bg.width = sidebar_bg.slimToolBarWidth
            }
        }
    }
}
