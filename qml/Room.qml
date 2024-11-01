import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import MainWorkspaceElements

DefaultFrame {
    id: room
    anchors.fill: parent

    property alias roomName: roomName.text
    property alias roomCreatorName: roomCreatorName.text
    property int roomCreatorID
    property var taskCreationWindow

    signal openTaskCreationForm()

    Text {
        id: roomName
        objectName: qsTr("name")
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
        id: roomCreatorName
        objectName: qsTr("roomCreatorName")
        anchors.left: parent.left
        anchors.top: roomName.bottom
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
        anchors.top: roomCreatorName.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.horizontal: ScrollBar {
            anchors.bottom: parent.bottom
        }

        GridLayout {
            objectName: qsTr("tasksContainer")
            id: roomContainer
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
        onClickFunction: function () {
            openTaskCreationForm()
        }
    }
}
