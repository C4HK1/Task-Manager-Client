import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements

DefaultFrame {
    property alias taskName: taskName.text
    property alias taskDescription: taskDescription.text

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
            spacing: 10

            RowLayout {
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                Layout.topMargin: 20
                spacing: parent.width - editButton.width - taskName.width - 40

                Text {
                    id: taskName
                    objectName: qsTr("taskName")

                    Layout.alignment: Qt.AlignTop

                    font.pixelSize: 30
                    color: "white"
                    elide: Text.ElideLeft
                }

                Rectangle {
                    id: editButton

                    Layout.alignment: Qt.AlignRight

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

            Text {
                id: taskDescription
                objectName: qsTr("taskDescription")

                Layout.leftMargin: 20
                Layout.rightMargin: 20
                Layout.bottomMargin: 20
                Layout.fillWidth: true

                font.pixelSize: 16
                color: "white"
                elide: Text.ElideRight
                wrapMode: Text.Wrap
                textFormat: TextEdit.MarkdownText
            }
        }
    }
}
