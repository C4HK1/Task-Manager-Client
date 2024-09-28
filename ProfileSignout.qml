import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts
import AppFrontend.LoginPage

Frame {
    id: profile_signout_form
    anchors.fill: parent

    property var object;

    Rectangle {
        width: 500
        height: 360
        color: "#303030"
        radius: 20
        anchors.centerIn: parent
        z: 3

        property bool focused: true

        GridLayout {
            id: form
            width: 200
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            z: 4

            columns: 1

            DefaultButton {
                text: qsTr("Sign out")
                Layout.fillWidth: true
                Layout.preferredHeight: 33

                onClicked: {
                    MainApplication.outFromAccount()
                }
            }
        }

        MouseArea {
            anchors.fill: parent;
        }
    }

    MouseArea {
        anchors.fill: parent;

        onClicked: {
            profile_signout_form.destroy();
        }
    }
}
