import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements

DefaultFrame {
    property alias taskName: taskName.text
    property alias taskDescription: taskDescription.text

    property alias year: year.text
    property alias month: month.text
    property alias day: day.text
    property alias hour: hour.text
    property alias minute: minute.text

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
            spacing: 15

            RowLayout {
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                Layout.topMargin: 20
                spacing: parent.width - editButton.width - taskName.width - 40

                TextField {
                    id: taskName
                    objectName: qsTr("taskName")

                    font.pixelSize: 30
                    Layout.preferredWidth: 350
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

            RowLayout {
                Layout.leftMargin: 20
                Layout.rightMargin: 20

                TextField {
                    id: year
                    Layout.preferredWidth: 45
                    font.pixelSize: 16
                    color: "white"
                    maximumLength: 4
                }
                Text {
                    text: "/"
                    color: "white"
                    font.pixelSize: 16
                }
                TextField {
                    id: month
                    Layout.preferredWidth: 27
                    font.pixelSize: 16
                    color: "white"
                    maximumLength: 2
                }
                Text {
                    text: "/"
                    color: "white"
                    font.pixelSize: 16
                }
                TextField {
                    id: day
                    Layout.preferredWidth: 27
                    font.pixelSize: 16
                    color: "white"
                    maximumLength: 2
                }

                TextField {
                    id: hour
                    Layout.leftMargin: 10
                    Layout.preferredWidth: 27
                    font.pixelSize: 16
                    color: "white"
                    maximumLength: 2
                }
                Text {
                    text: ":"
                    color: "white"
                    font.pixelSize: 16
                }
                TextField {
                    id: minute
                    Layout.preferredWidth: 27
                    font.pixelSize: 16
                    color: "white"
                    maximumLength: 2
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
                height: 300

                Flickable {
                    id: descrFlickable
                    anchors.fill: parent

                    contentHeight: taskDescription.height
                    boundsBehavior: Flickable.StopAtBounds
                    clip: true

                    ScrollBar.vertical: ScrollBar {
                        anchors.right: parent.right
                    }

                    property int lastContentHeight: contentHeight

                    function ensureVisible(r) {
                        if (contentX >= r.x)
                            contentX = r.x;
                        else if (contentX+width <= r.x+r.width)
                            contentX = r.x+r.width-width;
                        if (contentY >= r.y)
                            contentY = r.y;
                        else if (contentY+height <= r.y+r.height)
                            contentY = r.y+r.height-height;
                    }

                    TextEdit {
                        id: taskDescription
                        objectName: qsTr("taskDescription")
                        width: parent.width
                        height: Math.max(descrHolder.height, contentHeight)

                        font.pixelSize: 16
                        color: "white"

                        wrapMode: TextEdit.Wrap

                        onCursorRectangleChanged: { descrFlickable.ensureVisible(cursorRectangle) }

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
