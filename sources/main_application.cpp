#include "main_application.h"
#include "network_manager.h"
#include "loggining_page.h"
#include "registration_page.h"
#include "home_page_contents.h"
#include "home_page.h"

MainApplication::MainApplication(int argc, char **argv) :
    QGuiApplication(argc, argv),
    netManager(NetworkManager::getInstance()),
    consumer(Kafka::Consumer::getInstance("1")),
    engine(new QQmlEngine()) {

    connect(netManager, &NetworkManager::finishProfileAuthenticationResponseHandling, this, &MainApplication::handleAuthentication);

    QQmlComponent *component = new QQmlComponent(engine, QUrl::fromLocalFile("qml/MainWindow.qml"));
    mainWindow = qobject_cast<QQuickWindow*>(component->create(engine->rootContext()));
    component->deleteLater();

    nav_service = new NavigationService(mainWindow->contentItem());

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
    mainWindow->deleteLater();
    engine->deleteLater();
    nav_service->deleteLater();
}

//Methods

void MainApplication::handleAuthentication(Models::ServerStatus serverStatus, std::string topic) {
    if(!serverStatus.status) {
        this->consumer->addTopics(topic.c_str());
        this->consumer->startListen();

        this->switchToHomePage();
    } else {
        this->switchToLogginingPage();
    }
}

//Page part
template <typename ElementType, typename ...Args> requires IsPage<ElementType>
BasePage* MainApplication::createElement(Args... args) {
    return new ElementType(engine, args...);
}


//Switchers
void MainApplication::switchToRegistrationPage() {
    nav_service->switchTo(createElement<RegistrationPage>(this));
}

void MainApplication::switchToLogginingPage() {
    nav_service->switchTo(createElement<LogginingPage>(this));
}

void MainApplication::switchToHomePage() {
    nav_service->switchTo(createElement<HomePage>(this));
}
