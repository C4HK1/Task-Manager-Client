#include <nlohmann/json.hpp>

#include "room_creation_page.h"
#include "main_page.h"

RoomCreationPage::RoomCreationPage(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage) :
        BasePage(engine, container, "qml/RoomCreation.qml"),
        mainPage(mainPage) {
    connect(netManager, &NetworkManager::finishCreateRoomResponseHandling, this, &RoomCreationPage::finishCreateRoom);
    connect(this->getObject(), SIGNAL(createRoom(QString, QString)), this, SLOT(createRoom(QString, QString)));
}

void RoomCreationPage::createRoom(QString roomName, QString description) {
    this->netManager->sendCreateRoomRequest(roomName, description);
}

void RoomCreationPage::finishCreateRoom(ServerStatus serverStatus, Room room) {
    if (!serverStatus.status) {
        this->mainPage->switchToRoomPage(room);
    } else {
        qInfo() << "error room creatio with status: " << serverStatus.status;
    }
}

RoomCreationPage::~RoomCreationPage() {}
