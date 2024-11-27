import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements

DefaultFrame {
    property alias taskName: taskName.text
    property alias taskDescription: taskDescription.text

    signal switchToViewPage()

    Flickable {
        id: flickable
        objectName: qsTr("flickable")
        anchors.fill: parent

        contentHeight: contentHolder.height
        boundsBehavior: Flickable.StopAtBounds
        clip: true

        ScrollBar.vertical: ScrollBar {
            anchors.right: parent.right
        }

        ColumnLayout {
            id: contentHolder
            width: parent.width
            spacing: 10

            RowLayout {
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                Layout.topMargin: 20
                spacing: parent.width - editButton.width - taskName.width - 40

                TextField {
                    id: taskName
                    objectName: qsTr("taskName")

                    font.pixelSize: 30
                    width: 300 // why doesn't affect???
                    color: "white"
                }

                Rectangle {
                    id: editButton

                    width: 40
                    height: 40
                    radius: 10

                    color: "#404040"

                    Image {
                        source: "images/visible.png"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: 30
                        height: 30
                        mipmap: true
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

                        onClicked: {
                            switchToViewPage()
                        }
                    }
                }
            }

            Rectangle {
                id: descrHolder
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                Layout.fillWidth: true

                color: "#353535"
                border.color: "transparent"
                border.width: 1

                width: parent.width - 40
                height: 200

                Flickable {
                    anchors.fill: parent

                    contentHeight: taskDescription.height
                    boundsBehavior: Flickable.StopAtBounds
                    clip: true

                    ScrollBar.vertical: ScrollBar {
                        anchors.right: parent.right
                    }

                    TextEdit {
                        id: taskDescription
                        objectName: qsTr("taskDescription")
                        width: parent.width
                        height: Math.max(descrHolder.height, contentHeight)

                        font.pixelSize: 16
                        color: "white"

                        wrapMode: TextEdit.Wrap
                        verticalAlignment: TextInput.AlignTop

                        onActiveFocusChanged: {
                            if (activeFocus) {
                                descrHolder.border.color = "#f5701d"
                            } else {
                                descrHolder.border.color = "transparent"
                            }
                        }
                    }
                }
            }
        }
    }
}
