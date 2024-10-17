import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts
import MainWorkspaceElements
import AppFrontend

DefaultFrame {
    id: root

    signal switchToWidgetRooms()
    signal switchToListRooms()
    signal switchToTasks()
    signal switchToProfile()
    signal switchToSettings()

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
        z: 1

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

        SidebarButton {
            width: parent.width
            id: t
            name: "XZ"
            font_size: 22

            onClickFunction: function() {
                if(widgetRoomsView){
                    switchToWidgetRooms()
                } else {
                    switchToListRooms()
                }
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

                    tasks_list = root.createImageObject("MainWorkspaceElements/Tasks.qml", sidebar_bg)
                    tasks_list.anchors.top = tool_bar_tasks.bottom
                    tasks_list.width = parent.width
                    tasks_list.height = parent.height - tool_bar_tasks.height - tool_bar_profile.height - t.height

                    switchToTasks()
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

                    profile_tools = root.createImageObject("MainWorkspaceElements/ProfileTools.qml", sidebar_bg)
                    profile_tools.anchors.top = tool_bar_profile.bottom
                    profile_tools.width = parent.width
                    profile_tools.height = parent.height - tool_bar_tasks.height - tool_bar_profile.height - t.height
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
                switchToWidgetRooms()
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
                switchToListRooms()
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

    Rectangle {
        color: "transparent"
        objectName: qsTr("workspace")
        anchors.top: topbar_bg.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: parent.width - sidebar_bg.slimToolBarWidth
        border.width: 0
    }
}
