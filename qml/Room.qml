import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import MainWorkspaceElements

DefaultFrame {
    Flickable {
        objectName: qsTr("flickable")
        anchors.fill: parent
        leftMargin: 10
        rightMargin: 10
        topMargin: 10
        bottomMargin: 10

        contentHeight: room_container.height
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.horizontal: ScrollBar {
            anchors.bottom: parent.bottom
        }

        ColumnLayout {
            objectName: qsTr("tasks_container")
            id: room_container
            width: 100
        }
    }

    Task {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
    }
}
