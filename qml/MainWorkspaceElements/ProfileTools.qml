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
            name: "Profile"
            id: profile
            fontSize: 16
            onClickFunction: function () {
                switchToProfile()
            }
        }

        SidebarButton {
            name: "Settings"
            id: settings
            fontSize: 16
            onClickFunction: function() {
                switchToSettings()
            }
        }

        SidebarButton {
            name: "Sign Out"
            id: profileSignout
            fontSize: 16

            property var profileSignoutPage;

            onClickFunction: function() {
                if (profileSignoutPage === undefined) {
                    profileSignoutPage = root.createImageObject("DefaultElements/DefaultForm.qml", root, {"buttonText": qsTr("Sign Out"), "option": function() {loggout()}})
                }
            }
        }

        SidebarButton {
            name: "Delete Account"
            id: profileDeleting
            fontSize: 16

            property var profileDeletingPage;

            onClickFunction: function() {
                if (profileDeletingPage === undefined) {
                    profileDeletingPage = root.createImageObject("DefaultElements/DefaultForm.qml",
                                                                 root,
                                                                 {
                                                                     "buttonText": qsTr("Delete profile"),
                                                                     "option": function() {deleteProfile()}
                                                                 })
                }
            }
        }
    }
}
