import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts
import AppFrontend.LoginPage

DefaultFrame {
    GridLayout {
        id: form
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: 200

        rows: 5
        columns: 1

        DefaultButton {
            Layout.row: 3
            text: qsTr("Sign out")
            Layout.fillWidth: true
            Layout.preferredHeight: 33

            onClicked: {
                NetworkManager.sendProfileDeletingRequest()
            }
        }
    }
}
