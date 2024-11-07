import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts

Frame {
    id: form
    anchors.fill: parent
    z: 2

    property var room: parent
    property var profiles: []

    signal findProfilesWithSuchName(string name)
    signal invite(var recieversID, int roomCreatorID, string roomName)
    signal closeInvitationForm()

    Rectangle {
        width: 500
        height: 360
        color: "#303030"
        radius: 20
        anchors.centerIn: parent
        z: 3

        property bool focused: true

        GridLayout {
            width: 200
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            columns: 1

            TextField {
                Layout.row: 1
                id: name
                width: 500

                onTextChanged: function() {
                    console.log(name.text)
                    findProfilesWithSuchName(name.text)
                }
            }

            GridLayout {
                Layout.row: 2
                columnSpacing: 3
                flow: GridLayout.LeftToRight

                Repeater {
                    id: paramRepeater
                    model: [
                        {name: qsTr("profileName"), text: qsTr("profileID"), width: 300}
                    ]

                    Rectangle {
                        Text {
                            text: modelData.name
                        }
                    }
                }
            }

            DefaultButton {
                Layout.row: 3
                id: button
                Layout.fillWidth: true
                Layout.preferredHeight: 33
                text: "invite"

                onClicked: {
                    console.log("invite")
                    invite(recieversID, room.roomcraetorID, room.roomName)
                }
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
