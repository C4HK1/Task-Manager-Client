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

void MainApplication::handleAuthentication(ServerStatus serverStatus) {
    if(!serverStatus.status) {
        this->switchToHomePage();
    } else {
        this->switchToLogginingPage();
    }
}

void MainApplication::SetCurrentPage(BasePage *page) {
    if(curPage != nullptr) {
        curPage->deleteLater();
    }

    curPage = page;
}

template <typename PageType, typename ...Args> requires IsPage<PageType>
void MainApplication::switchPage(Args... args){
    SetCurrentPage(new PageType(engine, mainWindow->contentItem(), args...));
}

void MainApplication::switchToRegistrationPage() {
    switchPage<RegistrationPage>();
    connect(dynamic_cast<RegistrationPage *>(this->curPage), &RegistrationPage::switchToLogginingPage, this, &MainApplication::switchToLogginingPage);
    connect(dynamic_cast<RegistrationPage *>(this->curPage), &RegistrationPage::switchToHomePage, this, &MainApplication::switchToHomePage);
}

void MainApplication::switchToLogginingPage() {
    switchPage<LogginingPage>();
    connect(dynamic_cast<LogginingPage *>(this->curPage), &LogginingPage::switchToRegistrationPage, this, &MainApplication::switchToRegistrationPage);
    connect(dynamic_cast<LogginingPage *>(this->curPage), &LogginingPage::switchToHomePage, this, &MainApplication::switchToHomePage);
}

void MainApplication::switchToHomePage() {
    switchPage<MainPage>();
    connect(dynamic_cast<MainPage *>(this->curPage), &MainPage::switchToRegistrationPage, this, &MainApplication::switchToRegistrationPage);
    connect(dynamic_cast<MainPage *>(this->curPage), &MainPage::switchToLogginingPage, this, &MainApplication::switchToLogginingPage);
}

MainApplication::~MainApplication() {
    curPage->deleteLater();
    mainWindow->deleteLater();
    engine->deleteLater();
}
