import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import MainWorkspaceElements

DefaultFrame {
    id: room

    property alias room_name: room_name.text
    property alias owner_name: owner_name.text
    property int owner_id
    property var taskCreationWindow

    function handleTaskCreation(status) {
        if (status) {
            taskCreationWindow.destroy()
        } else {
            console.log("creation failed")
        }
    }

    Rectangle {
        id: room_info
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        Text {
            id: room_name
            objectName: qsTr("room_name")
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 15
            anchors.topMargin: 15
            color: "#FFFFFF"
            font.pixelSize: 18
            font.bold: true
            width: parent.width - anchors.leftMargin * 2
            wrapMode: Text.WordWrap
            maximumLineCount: 2
            elide: Text.ElideRight
        }

        Text {
            id: owner_name
            objectName: qsTr("owner_name")
            anchors.left: parent.left
            anchors.top: room_name.bottom
            anchors.leftMargin: 15
            anchors.topMargin: 10
            anchors.margins: 15
            color: "#FFFFFF"
            font.pixelSize: 16
            width: parent.width - anchors.leftMargin * 2
            wrapMode: Text.WordWrap
            maximumLineCount: 2
            elide: Text.ElideRight
        }
    }

    Flickable {
        objectName: qsTr("flickable")
        anchors.top: room_info.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        leftMargin: 10
        rightMargin: 10
        topMargin: 10
        bottomMargin: 10

        contentHeight: room_container.height
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.horizontal: ScrollBar {
            anchors.bottom: parent.bottom
        }

        ColumnLayout {
            objectName: qsTr("tasks_container")
            id: room_container
            width: 100
        }
    }

    TaskCreationButton {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
    }
}
