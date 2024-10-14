#include "main_application.h"
#include "network_manager.h"
#include "authorization_page.h"
#include "registration_page.h"
#include "main_page_contents.h"
#include "main_page.h"

MainApplication::MainApplication(int argc, char **argv) :
    QGuiApplication(argc, argv), net_manager(new NetworkManager(this)), engine(new QQmlEngine())
{
    QObject::connect(net_manager, &NetworkManager::authorizationResponseAccept, this, &MainApplication::handleAuthentication);

    qmlRegisterSingletonInstance("AppFrontend", 1, 0, "NetworkManager", net_manager);
    qmlRegisterSingletonInstance("AppFrontend", 1, 0, "MainApplication", this);

    QQmlComponent *component = new QQmlComponent(engine, QUrl::fromLocalFile("qml/MainWindow.qml"));
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
        switchPage<AuthorizationPage>();
        return;
    }

    file.open(QIODevice::ReadOnly);
    QByteArray token = file.readAll();
    file.close();
    net_manager->token = token;
    net_manager->sendAuthenticationRequest();
}

template <typename PageType, typename ...Args> requires IsPage<PageType>
void MainApplication::switchPage(Args... args){
    SetCurrentPage(new PageType(engine, main_window->contentItem(), args...));
}

void MainApplication::switchToRegister() {
    switchPage<RegistrationPage>();
}

void MainApplication::switchToSettings() {
    qobject_cast<MainPage*>(cur_page)->switchPage<SettingsPage>();
}

void MainApplication::switchToProfile() {
    qobject_cast<MainPage*>(cur_page)->switchPage<ProfilePage>();
}

void MainApplication::switchToWidgetRooms() {
    qobject_cast<MainPage*>(cur_page)->switchPage<WidgetRoomsPage>();
}

void MainApplication::switchToListRooms() {
    qobject_cast<MainPage*>(cur_page)->switchPage<ListRoomsPage>();
}

void MainApplication::switchToRoomCreation() {
    qobject_cast<MainPage*>(cur_page)->switchPage<RoomCreationPage>(net_manager);
}

void MainApplication::switchToRoom(RoomInfo *room) {
    qobject_cast<MainPage*>(cur_page)->switchPage<RoomPage>(room, net_manager);
}

void MainApplication::switchToTasks() {
    qobject_cast<MainPage*>(cur_page)->switchPage<TasksPage>();
}

void MainApplication::handleAuthentication(bool success) {
    qInfo() << "authentication status: " << success;
    if(success) {
        switchPage<MainPage>(net_manager);
        this->m_loginingError = false;
    } else {
        switchPage<AuthorizationPage>();
        this->m_loginingError = true;
    }

    emit loginingErrorChanged();
}

void MainApplication::outFromAccount()
{
    std::remove("data/authentication_key.organizer");
    switchPage<AuthorizationPage>();
}
