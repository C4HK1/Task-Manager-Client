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

    property alias room_name: room_name.text
    property alias owner_name: owner_name.text

    Text {
        id: room_name
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
        id: owner_name
        anchors.left: room_name.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 15
        color: "white"
        font.pixelSize: 14
        width: 150
        elide: Text.ElideRight
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            parent.color = "#303030"
        }

        onExited: {
            parent.color = "#242424"
        }
    }
}
