import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts
import AppFrontend.LoginPage

Flickable {
    anchors.fill: parent
    leftMargin: 15
    rightMargin: 15
    topMargin: 15
    bottomMargin: 15

    contentHeight: container.height
    boundsBehavior: Flickable.StopAtBounds
    // ScrollBar.vertical: ScrollBar {
    //     anchors.right: parent.right
    // }

    ColumnLayout {
        id: container
        width: parent.width

        SidebarButton {
            name: "Profile"
            id: profile_tools
            font_size: 16
            onClickFunction: function () {
                console.log("Profile")
            }
        }

        SidebarButton {
            name: "Settings"
            id: settings
            font_size: 16
            onClickFunction: function() {
                console.log("Settings")
            }
        }

        SidebarButton {
            name: "Sign Out"
            id: profile_signout
            font_size: 16

            property var profile_signout_page;

            onClickFunction: function() {
                if (profile_signout_page === undefined) {
                    profile_signout_page = root.createImageObject("ProfileSignout.qml", root)
                }
            }
        }

        SidebarButton {
            name: "Delete Account"
            id: profile_deleting
            font_size: 16

            property var profile_deleting_page;

            onClickFunction: function() {
                if (profile_deleting_page === undefined) {
                    profile_deleting_page = root.createImageObject("ProfileDeleting.qml", root)
                }
            }
        }
    }
}
