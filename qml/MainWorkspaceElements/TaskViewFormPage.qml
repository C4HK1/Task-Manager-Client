import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements
import qml.MainWorkspaceElements

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

        RowLayout {
            id: contentHolder
            width: parent.width

            ColumnLayout {
                Layout.rightMargin: 20
                Layout.leftMargin: 20
                Layout.preferredWidth: parent.width - sidemenu.width - 40
                spacing: 15

                Text {
                    id: taskName
                    objectName: qsTr("taskName")

                    Layout.maximumWidth: 400
                    Layout.topMargin: 20

                    font.pixelSize: 30
                    color: "white"
                    elide: Text.ElideLeft
                    wrapMode: Text.Wrap
                }

                RowLayout {
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

                    Layout.bottomMargin: 20
                    Layout.fillWidth: true
                    Layout.preferredWidth: parent.width

                    font.pixelSize: 16
                    elide: Text.ElideRight
                    wrapMode: Text.Wrap
                    textFormat: TextEdit.MarkdownText

                    color: "white"
                }
            }

            ColumnLayout {
                id: sidemenu
                Layout.rightMargin: 20
                Layout.preferredHeight: contentHolder.height

                Rectangle {
                    id: editButton

                    Layout.alignment: Qt.AlignRight | Qt.AlignTop
                    Layout.topMargin: 20

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

                Text {
                    Layout.topMargin: 20

                    font.bold: true
                    font.pixelSize: 16
                    color: "white"

                    text: "Assignees"
                }

                ColumnLayout {
                    id: assigneesHolder

                    Layout.maximumWidth: 200
                    Layout.preferredWidth: {
                        var w = children[0].width
                        for(var i = 1; i < children.length; ++i) {
                            w = Math.max(w, children[i].width)
                        }
                        w
                    }

                    ProfileStrip{}
                    ProfileStrip{}
                }

                Rectangle {
                    id: addAssigneeButton

                    Layout.topMargin: (assigneesHolder.children.length > 0) ? 5 : 0

                    width: 30
                    height: 30
                    radius: 15

                    color: "#404040"

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter

                        color: "white"
                        font.pixelSize: 18

                        text: "+"
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

                        }
                    }
                }

                Text {
                    Layout.topMargin: 20
                    font.bold: true
                    font.pixelSize: 16
                    color: "white"

                    text: "Reviewers"
                }

                ColumnLayout {
                    id: reviewersHolder
                    ProfileStrip{}
                }

                Rectangle {
                    id: addReviewerButton

                    Layout.topMargin: (reviewersHolder.children.length > 0) ? 5 : 0

                    width: 30
                    height: 30
                    radius: 15

                    color: "#404040"

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter

                        color: "white"
                        font.pixelSize: 18

                        text: "+"
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

                        }
                    }
                }
            }
        }
    }
}
