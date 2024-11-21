import QtQuick
import QtQuick.Controls
import qml.DefaultElements

DefaultFrame {
    property alias taskName: taskName.text
    property alias taskDescription: taskDescription.text

    signal switchToEditPage()

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

        font.pixelSize: 16
        color: "white"
        width: parent.width - 40
        elide: Text.ElideRight
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
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
