import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements
import qml.DefaultElements.Fonts
import qml.MainWorkspaceElements

DefaultFrame {
    id: room
    anchors.fill: parent

    property alias roomName: roomName.text
    property alias roomCreatorName: roomCreatorName.text
    property int roomCreatorID
    property var taskCreationWindow

    signal switchToTaskCreationForm()
    signal switchToInvitationForm()
    signal leaveFormRoom(int roomCreatorID, string roomName)

    GridLayout {
        id: roomInfo
        rows: 3
        columns: 1

        Text {
            Layout.row: 1
            id: roomName
            objectName: qsTr("name")
            color: "#FFFFFF"
            font.pixelSize: 18
            font.bold: true
            width: parent.width - anchors.leftMargin * 2
            wrapMode: Text.WordWrap
            maximumLineCount: 2
            elide: Text.ElideRight
        }

        Text {
            Layout.row: 2
            id: roomCreatorName
            objectName: qsTr("roomCreatorName")
            color: "#FFFFFF"
            font.pixelSize: 16
            width: parent.width - anchors.leftMargin * 2
            wrapMode: Text.WordWrap
            maximumLineCount: 2
            elide: Text.ElideRight
        }

        Text {
            Layout.row: 3
            text: qsTr("<html><a href=\"#\">Invite users?</a></html>")
            font: DefaultFont.defaultFont
            color: "#FFFFFF"
            onLinkActivated: switchToInvitationForm()
        }

        Text {
            Layout.row: 3
            leftPadding: 100
            text: qsTr("<html><a href=\"#\">Leave from room</a></html>")
            font: DefaultFont.defaultFont
            color: "#FFFFFF"
            onLinkActivated: leaveFormRoom(roomCreatorID, roomName.text)
        }
    }

    Flickable {
        objectName: qsTr("flickable")
        anchors.top: roomInfo.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.horizontal: ScrollBar {
            anchors.bottom: parent.bottom
        }

        GridLayout {
            objectName: qsTr("tasksContainer")
            id: tasksContainer
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
            switchToTaskCreationForm()
        }
    }
}
