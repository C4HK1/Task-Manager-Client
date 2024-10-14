import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import MainWorkspaceElements
import AppFrontend

DefaultFrame {
    Rectangle {
        id: info_top_bar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 3
        anchors.leftMargin: 3
        height: 30

        color: "#303030"

        Text {
            id: task_name
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 17
            color: "white"
            font.pixelSize: 16
            font.bold: true
            width: 200
            text: qsTr("Task name")
        }

        Text {
            anchors.left: task_name.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 13
            color: "white"
            font.pixelSize: 16
            font.bold: true
            width: 150
            text: qsTr("Room name")
        }
    }

    Flickable {
        objectName: qsTr("flickable")
        anchors.top: info_top_bar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 3

        contentHeight: task_container.height
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar {
            anchors.right: parent.right
        }

        GridLayout {
            id: task_container
            objectName: qsTr("list_container")
            width: parent.width
            rowSpacing: -2

            flow: GridLayout.LeftToRight
            columns: 1
        }
    }
}
