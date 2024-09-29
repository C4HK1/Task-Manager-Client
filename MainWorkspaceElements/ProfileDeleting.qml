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

        DefaultTextField {
            id: login_field
            Layout.row: 1
            Layout.fillWidth: true
            placeholderText: qsTr("Login")
        }

        DefaultTextField {
            id: password_field
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
                NetworkManager.sendAuthorizationRequest(login_field.text, password_field.text)
                error_field.visible = MainApplication.loginingError
            }
        }
        Text {
            Layout.row: 4
            Layout.topMargin: 50
            text: qsTr("Don't have an account? <html><a href=\"#\">Sign up</a></html>")
            font: DefaultFont.defaultFont
            color: "#FFFFFF"
            onLinkActivated: MainApplication.switchToRegister()
        }

        Text {
            id: error_field
            visible: false
            Layout.row: 5
            Layout.fillWidth: true
            color: "red";
            text: qsTr("Неверный логин или пароль!")
        }
    }
}
