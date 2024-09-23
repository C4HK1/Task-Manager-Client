import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Frame {
    anchors.fill: parent

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 36
        text: qsTr("Successful authentication")
        color: "#FFFFFF"
    }
}
