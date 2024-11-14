import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    Layout.fillWidth: true
    Layout.leftMargin: -1
    Layout.rightMargin: -1
    height: 50

    color: "#242424"
    border.width: 2
    border.color: "#303030"

    property alias senderName: senderName.text
    property alias roomName: roomName.text
    property int senderID
    property int roomCreatorID

    signal acceptInvite(int roomCreatorID, string roomName)
    signal deleteReceivedInvite(int senderID, int roomCreatorID, string roomName)

    Text {
        id: senderName
        objectName: qsTr("senderName")
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 20
        color: "white"
        font.pixelSize: 14
        font.bold: true
        width: 200
        elide: Text.ElideRight
    }

    Text {
        id: roomName
        objectName: qsTr("roomName")
        anchors.left: senderName.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 15
        color: "white"
        font.pixelSize: 14
        width: 150
        elide: Text.ElideRight
    }

    Button {
        id: acceptButton
        text: "accept"
        anchors.left: roomName.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 15

        onClicked: {
            acceptInvite(roomCreatorID, roomName.text)
        }
    }

    Button {
        id: discardButton
        text: "discard"
        anchors.left: acceptButton.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 15

        onClicked: {
            deleteReceivedInvite(senderID, roomCreatorID, roomName.text)
        }
    }
    // MouseArea {
    //     anchors.fill: parent
    //     hoverEnabled: true

    //     onClicked: openRoom(roomCreatorID, roomName.text)

    //     onEntered: {
    //         parent.border.color = "#404040"
    //         parent.border.width = 5
    //         parent.z = 2
    //     }

    //     onExited: {
    //         parent.border.color = "#303030"
    //         parent.border.width = 2
    //         parent.z = 0
    //     }
    // }
}
