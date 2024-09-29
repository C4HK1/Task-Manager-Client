import QtQuick
import QtQuick.Controls
import DefaultElements.Fonts

Rectangle {
    width: 30
    height: parent.height
    color: sidebar_bg.color

    property alias name: name.text
    property var onClickFunction: function() {}
    property string id: ""
    property bool selected: false

    id: id

    Text {
        id: name
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: "#FFFFFF"
        font.pixelSize: 10
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onClicked: onClickFunction()

        onEntered: {
            color = "#404040"
        }

        onExited: {
            color = sidebar_bg.color
        }
    }
}
