#include "main_application.h"
#include "network_manager.h"

MainApplication::MainApplication(int argc, char **argv) :
    QGuiApplication(argc, argv), net_manager(new NetworkManager(this)), engine(new QQmlEngine())
{
    QObject::connect(net_manager, &NetworkManager::authorizationResponseAccept, this, &MainApplication::handleAuthentication);

    qmlRegisterSingletonInstance("AppFrontend.LoginPage", 1, 0, "NetworkManager", net_manager);
    qmlRegisterSingletonInstance("AppFrontend.LoginPage", 1, 0, "MainApplication", this);

    QQmlComponent *component = new QQmlComponent(engine, QUrl::fromLocalFile("MainWindow.qml"));
    main_window = qobject_cast<QQuickWindow*>(component->create(engine->rootContext()));
    component->deleteLater();

    tryAuthenticate();
}

MainApplication::~MainApplication() {
    main_window->deleteLater();
    engine->deleteLater();
    net_manager->deleteLater();
}

void MainApplication::loadPage(QString moduleName) {
    if(cur_page != nullptr){
        cur_page->deleteLater();
    }

    QQmlComponent *component = new QQmlComponent(engine, QUrl::fromLocalFile(moduleName));
    cur_page = qobject_cast<QQuickItem*>(component->create(engine->rootContext()));
    component->deleteLater();

    cur_page->setParentItem(main_window->contentItem());
}

void MainApplication::tryAuthenticate() {
    QFile file("data/authentication_key.organizer");

    if(!file.exists()){
        loadPage("Authorization.qml");
        return;
    }

    file.open(QIODevice::ReadOnly);
    QByteArray token = file.readAll();
    file.close();
    net_manager->sendAuthenticationRequest(token);
}

void MainApplication::handleAuthentication(bool success) {
    qInfo() << "authentication status: " << success;
    this->m_loginingError = !success;
    if(success) {
        loadPage("MainWorkspace.qml");
    } else {
        loadPage("Authorization.qml");
    }
}
