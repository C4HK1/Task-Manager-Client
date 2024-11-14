#include "loggining_page.h"
#include "base_element.h"
#include "models.h"
#include "network_manager.h"
#include "widget_rooms.h"
#include "main_application.h"
#include "home_page.h"


//Object part
LogginingPage::LogginingPage(QQmlEngine *engine, MainApplication *mainApp) :
        BasePage(engine, "qml/Authorization.qml"),
        mainApp(mainApp) {
    connect(this->getObject(), SIGNAL(loggin(QString, QString)), this, SLOT(loggin(QString, QString)));
    connect(this->getObject(), SIGNAL(switchToRegistration()), this, SLOT(switchToRegistration()));

    connect(netManager, &NetworkManager::finishLogginResponseHandling, this, &LogginingPage::finishLoggining);
}

LogginingPage::~LogginingPage() {
}

void LogginingPage::update() {}
void LogginingPage::leave() {}

//Slots
void LogginingPage::loggin(QString login, QString password) {
    this->netManager->sendLogginRequest(login, password);
}

void LogginingPage::switchToRegistration() {
    this->mainApp->switchToRegistrationPage();
}

void LogginingPage::finishLoggining(Models::ServerStatus serverStatus, QByteArray jwt) {
    if (!serverStatus.status) {
        netManager->jwt = jwt;

        if(!QDir("data").exists()){
            QDir().mkdir("data");
        }

        QFile file("data/authentication_key.organizer");
        file.open(QIODevice::WriteOnly);
        file.write(netManager->jwt);
        file.close();

        this->mainApp->switchToHomePage();
    } else {
        qInfo() << "Profile loggining error status: " << serverStatus.status;
    }
}
