import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: profileRow
    Layout.fillWidth: true
    Layout.minimumHeight: 50
    Layout.leftMargin: -1
    Layout.rightMargin: -1

    color: "#242424"
    border.width: 2
    border.color: "#303030"

    property alias profileName: profileName.text
    property int profileID: 0
    property var invite: parent
    property bool isClicked: false

    Text {
        id: profileName
        objectName: qsTr("profileName")
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 20
        color: "white"
        font.pixelSize: 14
        font.bold: true
        width: 200
        elide: Text.ElideRight
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            isClicked = !isClicked

            if (isClicked) {
                invite.receiverID = profileID
                profileRow.color = "#404040"
            } else {
                invite.receiverID = 0
                profileRow.color = "#242424"
            }
        }

        onEntered: {
            parent.border.color = "#404040"
            parent.border.width = 5
            parent.z = 2
        }

        onExited: {
            parent.border.color = "#303030"
            parent.border.width = 2
            parent.z = 0
        }
    }
}
