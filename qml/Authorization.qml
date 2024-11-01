import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DefaultElements
import DefaultElements.Fonts

DefaultFrame {
    signal switchToRegistration()
    signal loggin(string login, string password)

    GridLayout {
        id: form
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: 200

        rows: 5
        columns: 1

        DefaultTextField {
            id: loginField
            Layout.row: 1
            Layout.fillWidth: true
            placeholderText: qsTr("Login")
        }

        DefaultTextField {
            id: passwordField
            Layout.row: 2
            Layout.fillWidth: true
            placeholderText: qsTr("Password")
            echoMode: "Password"
            passwordCharacter: qsTr("*")
        }

        DefaultButton {
            Layout.row: 3
            text: qsTr("Sign in")
            Layout.fillWidth: true
            Layout.preferredHeight: 33

            onClicked: {
                loggin(loginField.text, passwordField.text)
            }
        }

        Text {
            Layout.row: 4
            Layout.topMargin: 50
            text: qsTr("Don't have an account? <html><a href=\"#\">Sign up</a></html>")
            font: DefaultFont.defaultFont
            color: "#FFFFFF"
            onLinkActivated: switchToRegistration()
        }

        Text {
            id: errorField
            visible: false
            Layout.row: 5
            Layout.fillWidth: true
            color: "red";
            text: qsTr("Неверный логин или пароль!")
        }
    }
}
