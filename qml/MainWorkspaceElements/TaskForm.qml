import QtQuick
import QtQuick.Controls
import qml.DefaultElements

DefaultForm {
    property alias taskName: taskName.text
    property alias taskDescription: taskDescription.text

    Text {
        id: taskName
        objectName: qsTr("taskName")

        parent: container
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

        parent: container
        anchors.top: taskName.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 20

        font.pixelSize: 16
        color: "white"
        width: parent.width - 40
        elide: Text.ElideRight
        wrapMode: Text.WordWrap
        textFormat: TextEdit.MarkdownText
    }
}
