import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import MainWorkspaceElements
import AppFrontend

DefaultFrame {
    signal openRoom(TaskInfo ti)
    signal addTask(TaskInfo ti)

    function onAddTask(TaskInfo) {
        task_repeater.model.append(ti)
    }

    Rectangle {
        id: info_top_bar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 3
        anchors.leftMargin: 3
        height: 30

        color: "#202020"

        GridLayout {
            anchors.fill: parent
            columnSpacing: 10

            Repeater {
                model: [{text: qsTr("Task name")}, {text: qsTr("Room name")}]

                Text {
                    Layout.fillHeight: true
                    color: "white"
                    font.pixelSize: 16
                    font.bold: true
                    text: modelData.text
                }
            }
        }
    }

    Flickable {
        anchors.top: info_top_bar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 3

        contentHeight: task_container.height
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar {
            anchors.right: parent.right
        }

        GridLayout {
            id: task_container
            objectName: qsTr("list_container")
            width: parent.width
            rowSpacing: -2

            flow: GridLayout.LeftToRight
            columns: 1

            Repeater {
                id: task_repeater

                Rectangle {
                    Layout.fillWidth: true
                    Layout.leftMargin: -1
                    Layout.rightMargin: -1
                    height: 50

                    color: "#242424"
                    border.width: 2
                    border.color: "#303030"

                    Text {
                        Layout.fillHeight: true
                        color: "white"
                        font.pixelSize: 16
                        font.bold: true
                        text: modelData.task_name
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true

                        onClicked: openRoom(parent.modelData)

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
            }
        }
    }
}
