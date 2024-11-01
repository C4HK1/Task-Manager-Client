#include "registration_page.h"
#include "base_page.h"
#include "content_structures.h"
#include "network_manager.h"
#include "widget_rooms_page.h"
#include "main_application.h"
#include "main_page.h"

RegistrationPage::RegistrationPage(QQmlEngine *engine, QQuickItem *container) :
        BasePage(engine, container, "qml/Registration.qml") {
    connect(netManager, &NetworkManager::finishCreateProfileHandling, this, &RegistrationPage::finishCreateProfile);
    connect(this->getObject(), SIGNAL(createProfile(QString, QString, QString, QString, QString)), this, SLOT(createProfile(QString, QString, QString, QString, QString)));
}

void RegistrationPage::createProfile(QString name, QString login, QString password, QString email, QString phone) {
    this->netManager->sendCreateProfileRequest(name, login, password, email, phone);
}

void RegistrationPage::finishCreateProfile(ServerStatus serverStatus, QByteArray jwt) {
    if (!serverStatus.status) {
        netManager->jwt = jwt;

        if(!QDir("data").exists()){
            QDir().mkdir("data");
        }

        QFile file("data/authentication_key.organizer");
        file.open(QIODevice::WriteOnly);
        file.write(netManager->jwt);
        file.close();

        emit switchToHomePage();
    } else {
        qInfo() << "Profile creating error status: " << serverStatus.status;
    }
}

