import QtQuick
import AppFrontend

Rectangle {
    function createImageObject(str, root, params) {
        var component = Qt.createComponent(str)
        if (component.status === Component.Ready || component.status === Component.Error)
        {
            return finishCreation(component, root, params)
        } else {
            component.statusChanged.connect(finishCreation)
        }
    }
    function finishCreation(component, root, params) {
        if (component.status === Component.Ready) {
            return component.createObject(root, params)
        } else if (component.status === Component.Error) {
            console.log("Error loading component:", component.errorString())
        }
    }

    width: 35
    height: 35
    color: "#404040"
    radius: 5
    border.width: 1
    border.color: "#202020"

    property var onClickFunction: function() { parent.taskCreationWindow = createImageObject("TaskCreation.qml", parent) }

    id: id

    Text {
        id: name
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: "#FFFFFF"
        font.pixelSize: 24
        text: qsTr("+")
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onClicked: onClickFunction()

        onEntered: {
            parent.color = "#505050"
        }

        onExited: {
            parent.color = "#404040"
        }
    }
}
