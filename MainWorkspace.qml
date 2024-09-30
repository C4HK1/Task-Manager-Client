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
    function hideToolbar() {
        tool_bar_profile.name = "PS"
        tool_bar_tasks.name = "TS"
        t.name = "XZ"

        if (profile_tools !== undefined) {
            profile_tools.destroy()
            profile_tools = undefined
        }
        if (tasks_list !== undefined) {
            tasks_list.destroy()
            tasks_list = undefined
        }

        tool_bar_profile.anchors.bottom = undefined
        tool_bar_tasks.anchors.bottom = undefined
        tool_bar_tasks.anchors.top = t.bottom
        tool_bar_profile.anchors.top = tool_bar_tasks.bottom

        sidebar_bg.width = sidebar_bg.slimToolBarWidth

        mask.visible = false
    }
    function openToolbar() {
        sidebar_bg.width = sidebar_bg.toolBarWidth
        tool_bar_profile.name = "Profile settings"
        tool_bar_tasks.name = "Tasks"
        t.name = "XZ che eto"
        mask.visible = true
    }

    property var profile_tools;
    property var tasks_list;
    property bool widgetRoomsView: true

    Rectangle {
        id: mask
        anchors.left: sidebar_bg.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: topbar_bg.bottom
        z: 3

        color: "black"
        opacity: 0.5
        visible: false

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                root.hideToolbar()
            }
        }
    }

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

        Rectangle {
            anchors.fill: parent
            color: parent.color
            id: sidebar_container
            z: 2

            SidebarButton {
                width: parent.width
                id: t
                name: "XZ"
                font_size: 22

                onClickFunction: function() {
                    if(!widgetRoomsView){
                        MainApplication.switchToWidgetRooms()
                    } else {
                        MainApplication.switchToListRooms()
                    }

                    widgetRoomsView = !widgetRoomsView
                }
            }


            SidebarButton {
                width: parent.width
                anchors.top: t.bottom

                name: "TS"
                id: tool_bar_tasks
                font_size: 22

                onClickFunction: function() {
                    if (tasks_list === undefined) {
                        if (profile_tools !== undefined) {
                            profile_tools.destroy()
                            profile_tools = undefined
                        }

                        tool_bar_profile.anchors.top = undefined
                        tool_bar_profile.anchors.bottom = parent.bottom

                        tasks_list = root.createImageObject("GeneralElements/Tasks.qml", sidebar_container)
                        tasks_list.anchors.top = tool_bar_tasks.bottom
                        tasks_list.width = parent.width
                        tasks_list.height = parent.height - tool_bar_tasks.height - tool_bar_profile.height - t.height
                    }
                }
            }

            SidebarButton {
                width: parent.width
                anchors.top: tool_bar_tasks.bottom

                name: "PS"

                id: tool_bar_profile
                font_size: 22
                onClickFunction: function() {
                    if (profile_tools === undefined) {
                        if (tasks_list !== undefined) {
                            tasks_list.destroy()
                            tasks_list = undefined
                        }

                        tool_bar_profile.anchors.bottom = undefined
                        tool_bar_profile.anchors.top = tool_bar_tasks.bottom

                        profile_tools = root.createImageObject("GeneralElements/ProfileTools.qml", sidebar_container)
                        profile_tools.anchors.top = tool_bar_profile.bottom
                        profile_tools.width = parent.width
                        profile_tools.height = parent.height - tool_bar_tasks.height - tool_bar_profile.height - t.height
                    }
                }
            }
        }


        MouseArea {
            anchors.fill: sidebar_bg
            hoverEnabled: true

            onEntered: {
                root.openToolbar()
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
                root.hideToolbar()
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
    }
}
