#include "main_application.h"
#include "network_manager.h"
#include "authorization_page.h"
#include "registration_page.h"
#include "main_page.h"

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
    cur_page->deleteLater();
}

void MainApplication::SetCurrentPage(BasePage *page) {
    if(cur_page != nullptr) {
        cur_page->deleteLater();
    }

    cur_page = page;
}

void MainApplication::tryAuthenticate() {
    QFile file("data/authentication_key.organizer");

    if(!file.exists()){
        SetCurrentPage(new AuthorizationPage(engine, main_window->contentItem()));
        return;
    }

    file.open(QIODevice::ReadOnly);
    QByteArray token = file.readAll();
    file.close();
    net_manager->sendAuthenticationRequest(token);
}

void MainApplication::switchToRegister() {
    SetCurrentPage(new RegistrationPage(engine, main_window->contentItem()));
}

void MainApplication::handleAuthentication(bool success) {
    qInfo() << "authentication status: " << success;
    if(success) {
        SetCurrentPage(new MainPage(engine, main_window->contentItem()));
        this->m_loginingError = false;
    } else {
        SetCurrentPage(new AuthorizationPage(engine, main_window->contentItem()));
        this->m_loginingError = true;
    }
}

void MainApplication::outFromAccount()
{
    std::remove("data/authentication_key.organizer");
    SetCurrentPage(new AuthorizationPage(engine, main_window->contentItem()));
}
