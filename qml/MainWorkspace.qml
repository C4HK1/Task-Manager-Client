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
        toolBarProfile.name = "PS"
        toolBarTasks.name = "TS"
        t.name = "XZ"

        if (profileTools !== undefined) {
            profileTools.destroy()
            profileTools = undefined
        }
        if (tasksList !== undefined) {
            tasksList.destroy()
            tasksList = undefined
        }

        toolBarProfile.anchors.bottom = undefined
        toolBarTasks.anchors.bottom = undefined
        toolBarTasks.anchors.top = t.bottom
        toolBarProfile.anchors.top = toolBarTasks.bottom

        sidebarBG.width = sidebarBG.slimToolBarWidth

        mask.visible = false
    }
    function openToolbar() {
        sidebarBG.width = sidebarBG.toolBarWidth
        toolBarProfile.name = "Profile settings"
        toolBarTasks.name = "Tasks"
        t.name = "XZ che eto"
        mask.visible = true
    }

    property var profileTools;
    property var tasksList;
    property bool widgetRoomsView: true

    Rectangle {
        id: mask
        anchors.left: sidebarBG.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: topbarBG.bottom
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

        id: sidebarBG

        anchors.top: topbarBG.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: slimToolBarWidth
        z: 1

        color: "#303030"

        SidebarButton {
            width: parent.width
            id: t
            name: "XZ"
            fontSize: 22

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
            id: toolBarTasks
            fontSize: 22

            onClickFunction: function() {
                if (tasksList === undefined) {
                    if (profileTools !== undefined) {
                        profileTools.destroy()
                        profileTools = undefined
                    }

                    toolBarProfile.anchors.top = undefined
                    toolBarProfile.anchors.bottom = parent.bottom

                    tasksList = root.createImageObject("MainWorkspaceElements/Tasks.qml", sidebarBG)
                    tasksList.anchors.top = toolBarTasks.bottom
                    tasksList.width = parent.width
                    tasksList.height = parent.height - toolBarTasks.height - toolBarProfile.height - t.height

                    switchToTasks()
                }
            }
        }

        SidebarButton {
            width: parent.width
            anchors.top: toolBarTasks.bottom
            name: "PS"
            id: toolBarProfile
            fontSize: 22

            onClickFunction: function() {
                if (profileTools === undefined) {
                    if (tasksList !== undefined) {
                        tasksList.destroy()
                        tasksList = undefined
                    }

                    toolBarProfile.anchors.bottom = undefined
                    toolBarProfile.anchors.top = toolBarTasks.bottom

                    profileTools = root.createImageObject("MainWorkspaceElements/ProfileTools.qml", sidebarBG)
                    profileTools.anchors.top = toolBarProfile.bottom
                    profileTools.width = parent.width
                    profileTools.height = parent.height - toolBarTasks.height - toolBarProfile.height - t.height
                }
            }
        }


        MouseArea {
            anchors.fill: sidebarBG
            hoverEnabled: true

            onEntered: {
                root.openToolbar()
            }
        }
    }

    Rectangle {
        id: topbarBG
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        height: 30
        z: -1

        color: "#303030"

        TopbarRoomsViewButton {
            id: widgetViewButton
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
            id: listViewButton
            name: "L"
            anchors.top: parent.top
            anchors.right: widgetViewButton.left
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
        anchors.top: topbarBG.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: parent.width - sidebarBG.slimToolBarWidth
        border.width: 0
    }
}
