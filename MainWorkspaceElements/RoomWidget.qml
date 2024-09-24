import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    Layout.margins: 10
    Layout.fillWidth: true
    Layout.maximumWidth: 270
    height: 170
    radius: 20

    color: "#404040"

    property alias room_name: room_name.text
    property alias owner_name: owner_name.text

    Text {
        id: room_name
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 15
        anchors.topMargin: 15
        color: "#FFFFFF"
        font.pixelSize: 18
        font.bold: true
        width: parent.width - anchors.leftMargin * 2
        wrapMode: Text.WordWrap
        maximumLineCount: 2
        elide: Text.ElideRight
    }

    Text {
        id: owner_name
        anchors.left: parent.left
        anchors.top: room_name.bottom
        anchors.leftMargin: 15
        anchors.topMargin: 10
        anchors.margins: 15
        color: "#FFFFFF"
        font.pixelSize: 16
        width: parent.width - anchors.leftMargin * 2
        wrapMode: Text.WordWrap
        maximumLineCount: 2
        elide: Text.ElideRight
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            parent.color = "#505050"
        }

        onExited: {
            parent.color = "#404040"
        }
    }
}
