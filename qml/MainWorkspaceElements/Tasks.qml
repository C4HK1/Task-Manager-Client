import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts
import AppFrontend

Flickable {
    z: 2
    leftMargin: 15
    rightMargin: 15
    topMargin: 15
    bottomMargin: 15

    contentHeight: container.height
    boundsBehavior: Flickable.StopAtBounds

    ColumnLayout {
        id: container
        width: parent.width

        SidebarButton {
            name: "Task1"
            id: task1
            font_size: 16
            onClickFunction: function () {
                // MainApplication.switchToTask("Task1")
            }
        }

        SidebarButton {
            name: "Task2"
            id: task2
            font_size: 16
            onClickFunction: function () {
                // MainApplication.switchToTask("Task2")
            }
        }

        SidebarButton {
            name: "Task3"
            id: task3
            font_size: 16
            onClickFunction: function () {
                // MainApplication.switchToTask("Task3")
            }
        }

        SidebarButton {
            name: "Task4"
            id: task4
            font_size: 16
            onClickFunction: function () {
                // MainApplication.switchToTask("Task4")
            }
        }
    }
}
