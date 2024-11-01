#include "loggining_page.h"
#include "base_page.h"
#include "content_structures.h"
#include "network_manager.h"
#include "widget_rooms_page.h"
#include "main_application.h"
#include "main_page.h"

LogginingPage::LogginingPage(QQmlEngine *engine, QQuickItem *container) :
        BasePage(engine, container, "qml/Authorization.qml") {
    connect(netManager, &NetworkManager::finishLogginResponseHandling, this, &LogginingPage::finishLoggining);
    connect(this->getObject(), SIGNAL(switchToRegistration()), this, SLOT(switchToRegistration()));
    connect(this->getObject(), SIGNAL(loggin(QString, QString)), this, SLOT(loggin(QString, QString)));
}

void LogginingPage::loggin(QString login, QString password) {
    this->netManager->sendLogginRequest(login, password);
}

void LogginingPage::switchToRegistration() {
    emit this->switchToRegistrationPage();
}

void LogginingPage::finishLoggining(ServerStatus serverStatus, QByteArray jwt) {
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
        qInfo() << "Profile loggining error status: " << serverStatus.status;
    }
}
