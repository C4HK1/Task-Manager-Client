import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements
import qml.DefaultElements.Fonts

Frame {
    id: form
    anchors.fill: parent
    z: 2

    property string inviteSenderName;
    property string roomName;
    signal switchToInvitesPage()
    signal closeInviteMessage()


    Rectangle {
        width: 400
        height: 150
        color: "#303030"
        radius: 20
        z: 3

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top


        Text {
            color: "white"
            text: "You invited to room: " + roomName + " by user with name: " + inviteSenderName
        }

        MouseArea {
            anchors.fill: parent

            onClicked: {
                switchToInvitesPage()
            }
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            closeInviteMessage()
        }
    }
}
