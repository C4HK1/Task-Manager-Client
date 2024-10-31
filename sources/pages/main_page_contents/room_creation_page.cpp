#include <nlohmann/json.hpp>

#include "room_creation_page.h"
#include "main_page.h"

RoomCreationPage::RoomCreationPage(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage) :
        BasePage(engine, container, "qml/RoomCreation.qml"),
        mainPage(mainPage) {
    connect(netManager, &NetworkManager::finishCreateRoomResponseHandling, this, &RoomCreationPage::handleRoomCreationStatus);
}

void RoomCreationPage::handleRoomCreationStatus(ServerStatus serverStatus, Room room) {
    if (!serverStatus.status) {
        this->mainPage->switchToRoom(room);
    } else {
        QMetaObject::invokeMethod(object, "roomCreationFailed");
    }
}

RoomCreationPage::~RoomCreationPage() {}
