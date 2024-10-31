#include "main_application.h"
#include "network_manager.h"
#include "loggining_page.h"
#include "registration_page.h"
#include "main_page_contents.h"
#include "main_page.h"

MainApplication::MainApplication(int argc, char **argv) :
    QGuiApplication(argc, argv), netManager(NetworkManager::getInstance()), engine(new QQmlEngine())
{
    connect(netManager, &NetworkManager::finishProfileAuthenticationResponseHandling, this, &MainApplication::handleAuthentication);
    connect(netManager, &NetworkManager::finishDeleteProfileResponseHandling, this, &MainApplication::outFromAccount);

    qmlRegisterSingletonInstance("AppFrontend", 1, 0, "NetworkManager", netManager);
    qmlRegisterSingletonInstance("AppFrontend", 1, 0, "MainApplication", this);

    QQmlComponent *component = new QQmlComponent(engine, QUrl::fromLocalFile("qml/MainWindow.qml"));
    mainWindow = qobject_cast<QQuickWindow*>(component->create(engine->rootContext()));
    component->deleteLater();

    tryAuthenticate();
}

MainApplication::~MainApplication() {
    mainWindow->deleteLater();
    engine->deleteLater();
    curPage->deleteLater();
}

void MainApplication::SetCurrentPage(BasePage *page) {
    if(curPage != nullptr) {
        curPage->deleteLater();
    }

    curPage = page;
}

void MainApplication::tryAuthenticate() {
    QFile file("data/authentication_key.organizer");

    if(!file.exists()){
        switchPage<LogginingPage>(this);
        return;
    }

    file.open(QIODevice::ReadOnly);
    QByteArray jwt = file.readAll();
    file.close();
    netManager->jwt = jwt;
    netManager->sendProfileAuthenticationRequest();
}

template <typename PageType, typename ...Args> requires IsPage<PageType>
void MainApplication::switchPage(Args... args){
    SetCurrentPage(new PageType(engine, mainWindow->contentItem(), args...));
}

void MainApplication::switchToRegister() {
    switchPage<RegistrationPage>(this);
}

void MainApplication::handleAuthentication(ServerStatus serverStatus) {
    qInfo() << "authentication status: " << serverStatus.status;
    if(!serverStatus.status) {
        switchPage<MainPage>();
        this->loginingError = false;
    } else {
        switchPage<LogginingPage>(this);
        this->loginingError = true;
    }

    emit loginingErrorChanged();
}

void MainApplication::outFromAccount(ServerStatus serverStatus)
{
    if (!serverStatus.status) {
        std::remove("data/authentication_key.organizer");
        switchPage<LogginingPage>(this);
    }
}
