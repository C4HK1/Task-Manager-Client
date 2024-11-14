import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements
import qml.DefaultElements.Fonts

Frame {
    id: taskCreationForm
    anchors.fill: parent
    z: 2

    property var room: parent;

    signal createTask(int roomCreatorID, string roomName, string taskName, string description, string label, int status, int timeToLive);
    signal closeTaskCreationForm()

    Rectangle {
        width: 500
        height: 500
        color: "#303030"
        radius: 20
        anchors.centerIn: parent
        z: 3

        property bool focused: true

        GridLayout {
            id: taskSettings

            flow: GridLayout.LeftToRight
            columns: 2
            rows: 6
            rowSpacing: 30
            columnSpacing: 20

            Text {
                Layout.row: 0
                Layout.column: 0
                Layout.columnSpan: 2
                font.bold: true
                font.pixelSize: 36
                text: "Create task"
                color: "#FFFFFF"
            }

            Text {
                Layout.row: 1
                Layout.column: 0
                font.pixelSize: 18
                text: "task name"
                color: "#FFFFFF"
            }

            DefaultTextField {
                Layout.row: 1
                Layout.column: 1
                id: taskName
            }

            Text {
                Layout.row: 2
                Layout.column: 0
                font.pixelSize: 18
                text: "description"
                color: "#FFFFFF"
            }

            DefaultTextField {
                Layout.row: 2
                Layout.column: 1
                id: description
            }

            Text {
                Layout.row: 3
                Layout.column: 0
                font.pixelSize: 18
                text: "label"
                color: "#FFFFFF"
            }

            DefaultTextField {
                Layout.row: 3
                Layout.column: 1
                id: label
            }

            Text {
                Layout.row: 4
                Layout.column: 0
                font.pixelSize: 18
                text: "status"
                color: "#FFFFFF"
            }

            DefaultTextField {
                Layout.row: 4
                Layout.column: 1
                id: status
            }

            Text {
                Layout.row: 5
                Layout.column: 0
                font.pixelSize: 18
                text: "time to live"
                color: "#FFFFFF"
            }

            DefaultTextField {
                Layout.row: 5
                Layout.column: 1
                id: timeToLive
            }

            DefaultButton {
                Layout.columnSpan: 2
                text: "Create"

                onClicked: {
                    createTask(room.roomCreatorID,
                               room.roomName,
                               taskName.text,
                               description.text,
                               label.text,
                               parseInt(status.text),
                               parseInt(timeToLive.text))
                }
            }
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            closeTaskCreationForm()
        }
    }
}
