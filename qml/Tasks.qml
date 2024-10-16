import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import MainWorkspaceElements
import AppFrontend

DefaultFrame {
    id: root

    property string sortedBy: "task_name"
    property bool ascending: true

    signal sortBy(string by, bool ascending)

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
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            columnSpacing: 3
            flow: GridLayout.LeftToRight

            Repeater {
                id: param_repeater
                model: [
                    {name: qsTr("task_name"), text: qsTr("Task name"), width: 212},
                    {name: qsTr("room_name"), text: qsTr("Room name"), width: 200}
                ]

                Rectangle {
                    color: "#303030"
                    Layout.fillHeight: true
                    width: modelData.width

                    Text {
                        objectName: modelData.name
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        id: parameter_text
                        color: "white"
                        font.pixelSize: 16
                        font.bold: true
                        text: modelData.text
                    }

                    Image {
                        visible: modelData.name === sortedBy
                        id: arrow_icon
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        source: (ascending) ? "images/arrow_down.png" : "images/arrow_up.png"
                        width: 15
                        height: 15
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true

                        onClicked: {
                            if (sortedBy === modelData.name) {
                                ascending = !ascending
                                sortBy(sortedBy, ascending)
                            } else {
                                sortedBy = modelData.name
                                ascending = true
                                sortBy(sortedBy, ascending)
                            }
                        }

                        onEntered: {
                            parent.color = "#404040"
                        }

                        onExited: {
                            parent.color = "#303030"
                        }
                    }
                }
            }
        }
    }

    Flickable {
        objectName: qsTr("flickable")
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
        }
    }
}
