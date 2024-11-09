import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts

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
                switchToAllInvites()
            }
        }

        SidebarButton {
            name: "Received"
            id: receivedInvites
            fontSize: 16
            onClickFunction: function () {
                switchToReceivedInvites()
            }
        }

        SidebarButton {
            name: "Sended"
            id: sendedInvites
            fontSize: 16
            onClickFunction: function () {
                switchToSendedInvites()
            }
        }
    }
}
