import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements
import qml.MainWorkspaceElements

DefaultFrame {
    id: root

    property string sortedBy: "roomName"
    property bool ascending: true

    signal sortBy(string by, bool ascending)

    Rectangle {
        id: infoTopBar
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
                id: paramRepeater
                model: [
                    {name: qsTr("profile name"), text: qsTr("Sender name"), width: 212},
                    {name: qsTr("roomName"), text: qsTr("Room name"), width: 200}
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
                        id: parameterText
                        color: "white"
                        font.pixelSize: 16
                        font.bold: true
                        text: modelData.text
                    }

                    Image {
                        visible: modelData.name === sortedBy
                        id: arrowIcon
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
        anchors.top: infoTopBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 3

        contentHeight: invitesContainer.height
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar {
            anchors.right: parent.right
        }

        GridLayout {
            id: invitesContainer
            objectName: qsTr("listContainer")
            width: parent.width
            rowSpacing: -2

            flow: GridLayout.LeftToRight
            columns: 1
        }
    }
}
