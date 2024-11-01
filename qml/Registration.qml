import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts

DefaultFrame {
    signal createProfile(string name, string login, string password, string email, string phone)

    GridLayout {
        id: form
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: 200

        rows: 7
        columns: 1

        DefaultTextField {
            id: nameField
            Layout.row: 1
            Layout.fillWidth: true
            placeholderText: qsTr("Name")
        }

        DefaultTextField {
            id: loginField
            Layout.row: 2
            Layout.fillWidth: true
            placeholderText: qsTr("Login")
        }

        DefaultTextField {
            id: passwordField
            Layout.row: 3
            Layout.fillWidth: true
            placeholderText: qsTr("Password")
            echoMode: "Password"
            passwordCharacter: qsTr("*")
        }

        DefaultTextField {
            id: emailField
            Layout.row: 4
            Layout.fillWidth: true
            placeholderText: qsTr("Email")
        }

        DefaultTextField {
            id: phoneField
            Layout.row: 5
            Layout.fillWidth: true
            placeholderText: qsTr("Phone")
        }

        DefaultButton {
            Layout.row: 6
            text: qsTr("Sign up")
            Layout.fillWidth: true
            Layout.preferredHeight: 33

            onClicked: {
                createProfile(nameField.text,
                              loginField.text,
                              passwordField.text,
                              emailField.text,
                              phoneField.text)
            }
        }
    }
}
