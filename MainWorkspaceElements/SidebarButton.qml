import QtQuick
import QtQuick.Controls
import DefaultElements.Fonts

Rectangle {
    anchors.left: parent.left
    width: parent.width
    height: 70
    color: sidebar_bg.color

    property alias name: name.text
    property bool selected: false

    Text {
        id: name
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: "#FFFFFF"
        font.pixelSize: 36
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            color = "#404040"
        }

        onExited: {
            color = sidebar_bg.color
        }
    }
}
