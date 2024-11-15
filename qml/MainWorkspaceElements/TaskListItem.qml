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

    property alias taskName: taskName.text
    property alias roomName: roomName.text
    property alias creatorName: creatorName.text
    property alias label: label.text
    property alias labelColor: labelRect.color
    property alias labelBorderColor: labelRect.border.color
    property int roomCreatorID

    signal openRoom(int roomCreatorID, string roomName)

    Text {
        id: taskName
        objectName: qsTr("taskName")
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 15
        color: "white"
        font.pixelSize: 14
        font.bold: true
        width: 195
        elide: Text.ElideRight
    }

    Text {
        id: roomName
        objectName: qsTr("roomName")
        anchors.left: taskName.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 15
        color: "white"
        font.pixelSize: 14
        width: 190
        elide: Text.ElideRight
    }

    Text {
        id: creatorName
        objectName: qsTr("creatorName")
        anchors.left: roomName.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 15
        color: "white"
        font.pixelSize: 14
        width: 190
        elide: Text.ElideRight
    }

    Rectangle {
        id: labelRect
        objectName: qsTr("labelRect")
        anchors.left: creatorName.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 15

        width: label.width + 18
        height: label.height + 12
        radius: 15
        border.width: 2

        Text {
            id: label
            objectName: qsTr("label")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 10
            font.pixelSize: 14
            elide: Text.ElideRight
            color: "white"
        }
    }

    Rectangle {
        id: labelSeparator
        anchors.left: labelRect.right
        anchors.verticalCenter: parent.verticalCenter
        color: "transparent"
        width: 150 - labelRect.width
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onClicked: openRoom(roomCreatorID, roomName.text)

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
