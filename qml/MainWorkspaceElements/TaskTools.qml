import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import qml.DefaultElements
import qml.DefaultElements.Fonts

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
            name: "All"
            id: allTasks
            fontSize: 16
            onClickFunction: function () {
                console.log(switchToAllTasks)
                switchToAllTasks()
            }
        }

        SidebarButton {
            name: "Reviewed"
            id: reviewedTasks
            fontSize: 16
            onClickFunction: function () {
                switchToReviewedTasks()
            }
        }

        SidebarButton {
            name: "Assigned"
            id: assignedTasks
            fontSize: 16
            onClickFunction: function () {
                switchToAssignedTasks()
            }
        }
    }
}
