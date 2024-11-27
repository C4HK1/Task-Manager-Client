import QtQuick
import QtQuick.Controls
import qml.DefaultElements

DefaultFrame {
    property alias taskName: taskName.text
    property alias taskDescription: taskDescription.text

    signal switchToEditPage()

    Flickable {
        id: flickable
        objectName: qsTr("flickable")
        anchors.fill: parent

        contentHeight: parent.height
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar {
            anchors.right: parent.right
        }

        Text {
            id: taskName
            objectName: qsTr("taskName")

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 20

            font.pixelSize: 30
            color: "white"
            width: parent.width - 40
            elide: Text.ElideLeft
        }

        Text {
            id: taskDescription
            objectName: qsTr("taskDescription")

            anchors.top: taskName.bottom
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: 20

            width: parent.width - 40
            font.pixelSize: 16
            color: "white"
            elide: Text.ElideRight
            wrapMode: Text.Wrap
            textFormat: TextEdit.MarkdownText
        }

        Rectangle {
            id: editButton

            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 20

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
                    console.log(taskDescription.width)
                    switchToEditPage()
                }
            }
        }
    }
}
