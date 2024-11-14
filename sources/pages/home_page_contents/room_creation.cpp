#include <nlohmann/json.hpp>

#include "room_creation.h"
#include "home_page.h"

//Object part
RoomCreation::RoomCreation(QQmlEngine *engine, HomePage *homePage) :
        BasePage(engine, "qml/RoomCreation.qml"),
        homePage(homePage) {
    connect(netManager, &NetworkManager::finishCreateRoomResponseHandling, this, &RoomCreation::finishCreateRoom);
    connect(this->getObject(), SIGNAL(createRoom(QString, QString)), this, SLOT(createRoom(QString, QString)));
}

RoomCreation::~RoomCreation() {
}

void RoomCreation::update() {}


//Slots
void RoomCreation::createRoom(QString roomName, QString description) {
    this->netManager->sendCreateRoomRequest(roomName, description);
}

void RoomCreation::finishCreateRoom(Models::ServerStatus serverStatus, Models::Room room) {
    if (!serverStatus.status) {
        this->homePage->closePage();
        this->homePage->switchToRoom(room);
    } else {
        qInfo() << "error room creatio with status: " << serverStatus.status;
    }
}
