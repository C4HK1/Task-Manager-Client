import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements
import qml.DefaultElements.Fonts

Frame {
    id: taskCreationForm
    anchors.fill: parent
    z: 2

    property var room: parent
    property alias container: container

    signal closeForm()

    Rectangle {
        id: container
        width: 500
        height: 500
        color: "#303030"
        radius: 20
        anchors.centerIn: parent
        z: 3

        property bool focused: true
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            closeForm()
        }
    }

    onChildrenChanged: {
        for (var i = 1; i < children.length; ++i) {
            if(children[i] !== container) {
                children[i].parent = container
            }
        }
    }
}
