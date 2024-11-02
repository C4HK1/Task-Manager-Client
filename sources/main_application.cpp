#include "main_application.h"
#include "network_manager.h"
#include "loggining_page.h"
#include "registration_page.h"
#include "home_page_contents.h"
#include "home_page.h"

MainApplication::MainApplication(int argc, char **argv) :
    QGuiApplication(argc, argv), netManager(NetworkManager::getInstance()), engine(new QQmlEngine())
{
    connect(netManager, &NetworkManager::finishProfileAuthenticationResponseHandling, this, &MainApplication::handleAuthentication);

    QQmlComponent *component = new QQmlComponent(engine, QUrl::fromLocalFile("qml/MainWindow.qml"));
    mainWindow = qobject_cast<QQuickWindow*>(component->create(engine->rootContext()));
    component->deleteLater();

    QFile file("data/authentication_key.organizer");

    if(!file.exists()){
        this->switchToLogginingPage();
        return;
    }

    file.open(QIODevice::ReadOnly);
    QByteArray jwt = file.readAll();
    file.close();

    netManager->jwt = jwt;
    netManager->sendProfileAuthenticationRequest();
}

MainApplication::~MainApplication() {
    curPage->deleteLater();
    mainWindow->deleteLater();
    engine->deleteLater();
}

//Methods

void MainApplication::handleAuthentication(Models::ServerStatus serverStatus) {
    if(!serverStatus.status) {
        this->switchToHomePage();
    } else {
        this->switchToLogginingPage();
    }
}

//Page part
void MainApplication::SetCurrentPage(BaseElement *page) {
    if(curPage != nullptr) {
        curPage->deleteLater();
    }

    curPage = page;
}

template <typename PageType, typename ...Args> requires IsElement<PageType>
void MainApplication::switchPage(Args... args){
    SetCurrentPage(new PageType(engine, mainWindow->contentItem(), this, args...));
}

//Switchers
void MainApplication::switchToRegistrationPage() {
    switchPage<RegistrationPage>();
}

void MainApplication::switchToLogginingPage() {
    switchPage<LogginingPage>();
}

void MainApplication::switchToHomePage() {
    switchPage<HomePage>();
}
