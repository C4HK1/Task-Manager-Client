import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements
import qml.DefaultElements.Fonts

DefaultForm {
    id: form

    signal findProfilesWithSuchName(string name)
    signal invite(int recieverID, int roomCreatorID, string roomName)
    signal closeInvitationForm()

    TextField {
        parent: container
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
        parent: container
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
        parent: container
        anchors.top: profiles.bottom
        id: button
        width: parent.width
        text: "invite"

        onClicked: {
            invite(profilesContainer.receiverID, room.roomCreatorID, room.roomName)
        }
    }
}
