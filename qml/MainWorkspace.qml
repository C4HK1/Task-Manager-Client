import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements
import qml.DefaultElements.Fonts
import qml.MainWorkspaceElements

DefaultFrame {
    id: root

    signal switchToWidgetRooms()
    signal switchToListRooms()
    signal switchToProfile()
    signal switchToSettings()

    signal switchToLoggoutForm()
    signal switchToProfileDeleteForm()

    signal switchToAllTasks()
    signal switchToReviewedTasks()
    signal switchToAssignedTasks()

    signal switchToAllInvites()
    signal switchToReceivedInvites()
    signal switchToSendedInvites()

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
    function makeDefaultToolsAnchorsh() {
        if (profileTools !== undefined) {
            profileTools.destroy()
            profileTools = undefined
        }
        if (taskTools !== undefined) {
            taskTools.destroy()
            taskTools = undefined
        }
        if (inviteTools !== undefined) {
            inviteTools.destroy()
            inviteTools = undefined
        }


        toolBarProfile.anchors.bottom = undefined
        toolBarInvite.anchors.top = toolBarTask.bottom
        toolBarTask.anchors.top = toolBarHome.bottom
        toolBarProfile.anchors.top = toolBarInvite.bottom
    }

    function hideToolbar() {
        toolBarProfile.name = "PS"
        toolBarTask.name = "TS"
        toolBarInvite.name = "IT"
        toolBarHome.name = "HM"

        makeDefaultToolsAnchorsh()

        sidebarBG.width = sidebarBG.slimToolBarWidth

        mask.visible = false
    }
    function openToolbar() {
        sidebarBG.width = sidebarBG.toolBarWidth
        toolBarProfile.name = "Profile settings"
        toolBarTask.name = "Tasks"
        toolBarInvite.name = "Invites"
        toolBarHome.name = "Home"
        mask.visible = true
    }

    property var profileTools;
    property var taskTools;
    property var inviteTools;
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
            id: toolBarHome
            name: "HM"
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
            anchors.top: toolBarHome.bottom
            name: "TS"
            id: toolBarTask
            fontSize: 22

            onClickFunction: function() {
                if (taskTools === undefined) {
                    makeDefaultToolsAnchorsh()

                    taskTools = root.createImageObject("MainWorkspaceElements/TaskTools.qml", sidebarBG)
                    taskTools.anchors.top = toolBarTask.bottom
                    taskTools.width = parent.width
                    taskTools.height = parent.height - toolBarTask.height - toolBarInvite.height - toolBarProfile.height - toolBarHome.height

                    toolBarInvite.anchors.top = taskTools.bottom
                    toolBarProfile.anchors.bottom = parent.bottom

                    switchToAllTasks()
                }
            }
        }

        SidebarButton {
            width: parent.width
            anchors.top: toolBarTask.bottom
            name: "IT"
            id: toolBarInvite
            fontSize: 22

            onClickFunction: function() {
                if (inviteTools === undefined) {
                    makeDefaultToolsAnchorsh()

                    toolBarProfile.anchors.top = undefined
                    toolBarProfile.anchors.bottom = parent.bottom

                    inviteTools = root.createImageObject("MainWorkspaceElements/InviteTools.qml", sidebarBG)
                    inviteTools.anchors.top = toolBarInvite.bottom
                    inviteTools.width = parent.width
                    inviteTools.height = parent.height - toolBarTask.height - toolBarInvite.height - toolBarProfile.height - toolBarHome.height

                    switchToAllInvites()
                }
            }
        }

        SidebarButton {
            width: parent.width
            anchors.top: toolBarInvite.bottom
            name: "PS"
            id: toolBarProfile
            fontSize: 22

            onClickFunction: function() {
                if (profileTools === undefined) {
                    makeDefaultToolsAnchorsh()

                    profileTools = root.createImageObject("MainWorkspaceElements/ProfileTools.qml", sidebarBG)
                    profileTools.anchors.top = toolBarProfile.bottom
                    profileTools.width = parent.width
                    profileTools.height = parent.height - toolBarTask.height - toolBarInvite.height - toolBarInvite.height - toolBarProfile.height - toolBarHome.height
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
