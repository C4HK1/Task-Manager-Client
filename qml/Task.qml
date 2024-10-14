import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import MainWorkspaceElements

Rectangle {
    Layout.fillHeight: true
    Layout.preferredWidth: 200
    color: "#404040"

    // task_name, owner_name, owner_id;
    property alias task_name: task_name.text;
    property alias owner_name: owner_name.text;
    property string owner_id;

    Text {
        id: task_name
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 15
        anchors.topMargin: 15
        color: "#FFFFFF"
        font.pixelSize: 18
        font.bold: true
        width: parent.width - anchors.leftMargin * 2
        wrapMode: Text.WordWrap
        maximumLineCount: 2
        elide: Text.ElideRight
    }

    Text {
        id: owner_name
        anchors.left: parent.left
        anchors.top: task_name.bottom
        anchors.leftMargin: 15
        anchors.topMargin: 10
        anchors.margins: 15
        color: "#FFFFFF"
        font.pixelSize: 16
        width: parent.width - anchors.leftMargin * 2
        wrapMode: Text.WordWrap
        maximumLineCount: 2
        elide: Text.ElideRight
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
            console.log("task editing..")
        }
    }
}
