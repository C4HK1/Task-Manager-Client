#include "loggining_page.h"
#include "base_page.h"
#include "content_structures.h"
#include "network_manager.h"
#include "widget_rooms_page.h"
#include "main_application.h"
#include "main_page.h"

LogginingPage::LogginingPage(QQmlEngine *engine, QQuickItem *container, MainApplication *mainApp) :
        BasePage(engine, container, "qml/Authorization.qml"),
        mainApp(mainApp) {
    connect(netManager, &NetworkManager::finishLogginResponseHandling, this, &LogginingPage::finishLoggining);
}

void LogginingPage::finishLoggining(ServerStatus serverStatus, QByteArray jwt) {
    if (!serverStatus.status) {
        this->mainApp->switchPage<MainPage>();
        netManager->jwt = jwt;

        if(!QDir("data").exists()){
            QDir().mkdir("data");
        }

        QFile file("data/authentication_key.organizer");
        file.open(QIODevice::WriteOnly);
        file.write(netManager->jwt);
        file.close();
    } else {
        qInfo() << "Profile loggining error status: " << serverStatus.status;
    }
}
