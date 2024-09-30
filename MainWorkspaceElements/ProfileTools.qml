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
            name: "Profile"
            id: profile
            font_size: 16
            onClickFunction: function () {
                MainApplication.switchToProfile()
            }
        }

        SidebarButton {
            name: "Settings"
            id: settings
            font_size: 16
            onClickFunction: function() {
                MainApplication.switchToSettings()
            }
        }

        SidebarButton {
            name: "Sign Out"
            id: profile_signout
            font_size: 16

            property var profile_signout_page;

            onClickFunction: function() {
                if (profile_signout_page === undefined) {
                    profile_signout_page = root.createImageObject("DefaultElements/DefaultForm.qml", root, {"button_text": qsTr("Sign Out"), "option": function() {MainApplication.outFromAccount()}})
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
                    profile_deleting_page = root.createImageObject("DefaultElements/DefaultForm.qml", root, {"button_text": qsTr("Delete profile"), "option": function() {NetworkManager.sendProfileDeletingRequest()}})
                }
            }
        }
    }
}
