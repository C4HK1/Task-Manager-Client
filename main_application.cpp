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
}

void MainApplication::SetCurrentPage(BasePage *page) {
    if(cur_page != nullptr) {
        delete cur_page;
    }

    cur_page = page;
    page->SetContainer(main_window);
}

QQuickItem* MainApplication::loadQmlFrame(QString moduleName) {
    QQmlComponent *component = new QQmlComponent(engine, QUrl::fromLocalFile(moduleName));
    qInfo() << component->errors();
    QQuickItem *new_frame = qobject_cast<QQuickItem*>(component->create(engine->rootContext()));
    component->deleteLater();

    return new_frame;
}

void MainApplication::tryAuthenticate() {
    QFile file("data/authentication_key.organizer");

    if(!file.exists()){
        AuthorizationPage::loadPage(this);
        return;
    }

    file.open(QIODevice::ReadOnly);
    QByteArray token = file.readAll();
    file.close();
    net_manager->sendAuthenticationRequest(token);
}

void MainApplication::switchToRegister() {
    RegistrationPage::loadPage(this);
}

void MainApplication::handleAuthentication(bool success) {
    qInfo() << "authentication status: " << success;
    if(success) {
        MainPage::loadPage(this);
        this->m_loginingError = false;
    } else {
        AuthorizationPage::loadPage(this);
        this->m_loginingError = true;
    }
}
