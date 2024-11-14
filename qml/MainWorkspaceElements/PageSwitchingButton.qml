import QtQuick
import QtQuick.Controls
import qml.DefaultElements.Fonts
import qml.MainWorkspaceElements

Rectangle {
    width: 30
    height: parent.height
    color: sidebarBG.color

    property var onClickFunction: function() {}
    property string id: ""
    property bool selected: false

    id: id

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onClicked: onClickFunction()

        onEntered: {
            color = "#404040"
        }

        onExited: {
            color = sidebarBG.color
        }
    }
}
