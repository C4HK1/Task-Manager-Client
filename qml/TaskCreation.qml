import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import AppFrontend
import DefaultElements.Fonts

Frame {
    id: taskCreationForm
    anchors.fill: parent
    z: 2

    Rectangle {
        width: 500
        height: 360
        color: "#303030"
        radius: 20
        anchors.centerIn: parent
        z: 3

        property bool focused: true

        GridLayout {
            id: taskSettings

            flow: GridLayout.LeftToRight
            columns: 2
            rowSpacing: 30
            columnSpacing: 20

            Text {
                Layout.columnSpan: 2
                font.bold: true
                font.pixelSize: 36
                text: "Create task"
                color: "#FFFFFF"
            }

            Text {
                font.pixelSize: 18
                text: "task name"
                color: "#FFFFFF"
            }

            DefaultTextField {
                id: taskName
            }

            DefaultTextField {
                id: description
            }

            DefaultTextField {
                id: label
            }

            DefaultTextField {
                id: status
            }

            DefaultTextField {
                id: timeToLive
            }

            DefaultButton {
                Layout.columnSpan: 2
                text: "Create"

                onClicked: {
                    NetworkManager.sendCreateTaskRequest(room.roomCreatorID,
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
            taskCreationForm.destroy()
        }
    }
}
