#include "rooms_list.h"
#include "home_page.h"

//Object part
RoomsList::RoomsList(QQmlEngine *engine, QQuickItem *container, QString moduleName, QString itemName, HomePage *homePage) :
        BaseElement(engine, container, moduleName),
        itemComponent(new QQmlComponent(engine, QUrl::fromLocalFile(itemName))),
        homePage(homePage) {
    connect(this->getObject(), SIGNAL(switchToRoomCreation()), this, SLOT(switchToRoomCreation()));

    connect(netManager, &NetworkManager::finishGetProfileRoomsResponseHandling, this, &RoomsList::initializeContents);
    connect(netManager, &NetworkManager::finishGetRoomResponseHandling, this, &RoomsList::finishSwitchToRoom);

    netManager->sendGetProfileRoomsRequest();
}

RoomsList::~RoomsList(){
    for(auto &item : roomsItems) {
        item->deleteLater();
    }

    itemComponent->deleteLater();
}


//Slots
void RoomsList::initializeContents(Models::ServerStatus serverStatus, Models::Rooms rooms) {
    this->rooms = rooms;

    for(auto &room : this->rooms){
        this->createRoomItem(room);
        connect(room.roomItem, SIGNAL(switchToRoom(int, QString)), this, SLOT(switchToRoom(int, QString)));
    }
}

void RoomsList::switchToRoomCreation() {
    this->homePage->switchToRoomCreation();
}

void RoomsList::switchToRoom(int roomCreatorID, QString roomName) {
    this->netManager->sendGetRoomRequest(roomCreatorID, roomName);
}

void RoomsList::finishSwitchToRoom(Models::ServerStatus serverStatus, Models::Room room) {
    if (!serverStatus.status) {
        this->homePage->switchToRoom(room);
    } else {
        qInfo() << "error room entry with status: " << serverStatus.status;
    }
}
