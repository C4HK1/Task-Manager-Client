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

    property alias task_name: task_name.text
    property alias room_name: room_name.text

    Text {
        id: task_name
        objectName: qsTr("task_name")
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
        id: room_name
        objectName: qsTr("room_name")
        anchors.left: task_name.right
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
