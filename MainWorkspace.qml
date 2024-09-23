import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts
import MainWorkspaceElements

DefaultFrame {
    Rectangle {
        id: sidebar_bg
        anchors.left: parent.left
        height: parent.height
        width: 80

        color: "#303030"
    }

    Column {
        anchors.fill: sidebar_bg

        SidebarButton {
            SidebarButton.name: "R"
        }

        SidebarButton {

        }
        SidebarButton {

        }
    }
}
