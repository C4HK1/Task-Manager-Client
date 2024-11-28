import QtQuick
import QtQuick.Layouts
import qml.MainWorkspaceElements

Rectangle {
    Layout.topMargin: 5

    Layout.preferredWidth: img.width + txt.width + 15
    Layout.fillWidth: true
    height: 30
    radius: 15

    color: "#303030"

    border.width: 1
    border.color: "white"

    Image {
        id: img
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 5
        source: "images/midas.jpg"
        width: 27
        height: 27
        mipmap: true
    }

    Text {
        id: txt
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: img.right
        anchors.right: parent.right
        anchors.leftMargin: 5
        anchors.rightMargin: 5

        color: "white"
        font.pixelSize: 14
        elide: Text.ElideRight

        text: "King Midasssssssssss"
    }
}
