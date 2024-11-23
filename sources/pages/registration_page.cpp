#include "registration_page.h"
#include "base_element.h"
#include "models.h"
#include "network_manager.h"
#include "widget_rooms.h"
#include "home_page.h"

//Object part
RegistrationPage::RegistrationPage(QQmlEngine *engine, MainApplication *mainApp) :
        BasePage(engine, "qml/Registration.qml"),
        mainApp(mainApp) {
    connect(this->getObject(), SIGNAL(createProfile(QString, QString, QString, QString, QString)), this, SLOT(createProfile(QString, QString, QString, QString, QString)));

    connect(netManager, &NetworkManager::finishCreateProfileHandling, this, &RegistrationPage::finishCreateProfile);
}

RegistrationPage::~RegistrationPage() {
}

void RegistrationPage::update() {};
void RegistrationPage::leave() {};

//Slots
void RegistrationPage::createProfile(QString name, QString login, QString password, QString email, QString phone) {
    this->netManager->sendCreateProfileRequest(name, login, password, email, phone);
}

void RegistrationPage::finishCreateProfile(Models::ServerStatus serverStatus, QByteArray jwt) {
    if (!serverStatus.status) {
        netManager->jwt = jwt;

        if(!QDir("data").exists()){
            QDir().mkdir("data");
        }

        QFile file("data/authentication_key.organizer");
        file.open(QIODevice::WriteOnly);
        file.write(netManager->jwt);
        file.close();

        netManager->sendProfileAuthenticationRequest();
    } else {
        qInfo() << "Profile creating error status: " << serverStatus.status;
    }
}

