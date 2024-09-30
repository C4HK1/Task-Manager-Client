import QtQuick
import QtQuick.Controls
import DefaultElements.Fonts

Rectangle {
    width: parent.width
    height: 70
    color: sidebar_bg.color

    property alias name: name.text
    property alias font_size: name.font.pixelSize
    property var onClickFunction: function() {}
    property string id: ""
    property bool selected: false

    id: id

    Text {
        id: name
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: "#FFFFFF"
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onClicked: onClickFunction()

        onEntered: {
            color = "#404040"
            sidebar_bg.width = sidebar_bg.toolBarWidth
            mask.visible = true
        }

        onExited: {
            color = sidebar_bg.color
        }
    }
}
