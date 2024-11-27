import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements

DefaultFrame {
    property alias taskName: taskName.text
    property alias taskDescription: taskDescription.text
    property alias deadline: deadline.text
    property int deadlineStatus: 0

    signal switchToEditPage()

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
            spacing: 15

            RowLayout {
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                Layout.topMargin: 20
                spacing: parent.width - editButton.width - taskName.width - 40

                Text {
                    id: taskName
                    objectName: qsTr("taskName")

                    Layout.maximumWidth: 400

                    font.pixelSize: 30
                    color: "white"
                    elide: Text.ElideLeft
                    wrapMode: Text.Wrap
                }

                Rectangle {
                    id: editButton

                    Layout.alignment: Qt.AlignTop

                    width: 40
                    height: 40
                    radius: 10

                    color: "#404040"

                    Image {
                        source: "images/write.png"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: 25
                        height: 25
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
                            switchToEditPage()
                        }
                    }
                }
            }

            RowLayout {
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                spacing: 10

                Text {
                    id: deadline
                    objectName: qsTr("deadline")

                    font.pixelSize: 20
                    elide: Text.ElideRight

                    color: {
                        if (deadlineStatus === 1) {
                            "yellow"
                        } else if (deadlineStatus === 2) {
                            "red"
                        } else {
                            "white"
                        }
                    }
                }

                Image {
                    Layout.preferredWidth: 25
                    Layout.preferredHeight: 25

                    source: {
                        if(deadlineStatus === 1) {
                            "images/warning.png"
                        } else if (deadlineStatus === 2) {
                            "images/error.png"
                        } else {
                            ''
                        }
                    }

                    mipmap: true
                }
            }

            Text {
                id: taskDescription
                objectName: qsTr("taskDescription")

                Layout.leftMargin: 20
                Layout.rightMargin: 20
                Layout.bottomMargin: 20
                Layout.fillWidth: true

                font.pixelSize: 16
                elide: Text.ElideRight
                wrapMode: Text.Wrap
                textFormat: TextEdit.MarkdownText

                color: "white"
            }
        }
    }
}
