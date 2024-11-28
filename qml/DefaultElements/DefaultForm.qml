import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements
import qml.DefaultElements.Fonts

DefaultFrame {
    id: taskCreationForm
    anchors.fill: parent
    z: 3

    property var room: parent
    property alias container: container

    signal closeForm()

    Rectangle {
        id: container
        width: 600
        height: 500
        color: "#303030"
        radius: 20
        anchors.centerIn: parent
        z: 4

        property bool focused: true
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        z: 3

        onClicked: {
            closeForm()
        }
    }

    onChildrenChanged: {
        for (var i = 2; i < children.length; ++i) {
            if(children[i] !== container) {
                children[i].parent = container
            }
        }
    }
}
