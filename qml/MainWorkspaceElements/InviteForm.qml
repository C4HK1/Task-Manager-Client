import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements
import qml.DefaultElements.Fonts

Frame {
    id: form
    anchors.fill: parent
    z: 2

    property var room: parent

    signal findProfilesWithSuchName(string name)
    signal invite(int recieverID, int roomCreatorID, string roomName)
    signal closeInvitationForm()

    Rectangle {
        width: 500
        height: 360
        color: "#303030"
        radius: 20
        anchors.centerIn: parent
        z: 3

        property bool focused: true

        TextField {
            anchors.top: parent.top
            id: name
            width: 500

            onTextChanged: function() {
                findProfilesWithSuchName(name.text)
            }
        }

        Flickable {
            id: profiles
            width: parent.width
            height: profilesContainer.height
            anchors.top: name.bottom
            objectName: qsTr("flickable")

            boundsBehavior: Flickable.StopAtBounds

            ScrollBar.vertical: ScrollBar {
                anchors.right: parent.right
            }

            GridLayout {
                id: profilesContainer

                property int receiverID: 0
                objectName: qsTr("profilesContainer")
                width: parent.width
                rowSpacing: -2

                flow: GridLayout.LeftToRight
                columns: 1
            }
        }

        DefaultButton {
            anchors.top: profiles.bottom
            id: button
            width: parent.width
            text: "invite"

            onClicked: {
                invite(profilesContainer.receiverID, room.roomCreatorID, room.roomName)
            }
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            closeInvitationForm()
        }
    }
}
