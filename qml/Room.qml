import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import MainWorkspaceElements

DefaultFrame {
    function taskCreated() {
        taskCreationWindow.destroy()
    }

    function taskCreationFailed() {
        console.log("task creation failed")
    }

    id: room
    anchors.fill: parent

    property alias room_name: room_name.text
    property alias owner_name: owner_name.text
    property int owner_id
    property var taskCreationWindow

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

    Flickable {
        objectName: qsTr("flickable")
        anchors.top: owner_name.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.horizontal: ScrollBar {
            anchors.bottom: parent.bottom
        }

        GridLayout {
            objectName: qsTr("tasks_container")
            id: room_container
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            rows: 1
        }
    }

    TaskCreationButton {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
    }
}
