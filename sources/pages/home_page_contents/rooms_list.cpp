#include "rooms_list.h"
#include "home_page.h"

//Object part
RoomsList::RoomsList(QQmlEngine *engine, QString moduleName, QString itemName, HomePage *homePage) :
        BasePage(engine, moduleName),
        itemComponent(new QQmlComponent(engine, QUrl::fromLocalFile(itemName))),
        homePage(homePage) {
    connect(object, SIGNAL(switchToRoomCreation()), this, SLOT(switchToRoomCreation()));
    connect(object, SIGNAL(sortBy(QString,bool)), this, SLOT(sortBy(QString,bool)));
}

RoomsList::~RoomsList(){
    clearContents();
    itemComponent->deleteLater();
}

void RoomsList::update() {
    connect(netManager, &NetworkManager::finishGetProfileRoomsResponseHandling, this, &RoomsList::initializeContents);
    connect(netManager, &NetworkManager::finishGetRoomResponseHandling, this, &RoomsList::finishSwitchToRoom);
    netManager->sendGetProfileRoomsRequest();
}

void RoomsList::leave() {
    disconnect(netManager, &NetworkManager::finishGetProfileRoomsResponseHandling, this, &RoomsList::initializeContents);
    disconnect(netManager, &NetworkManager::finishGetRoomResponseHandling, this, &RoomsList::finishSwitchToRoom);
    clearContents();
}

//Slots
void RoomsList::initializeContents(Models::ServerStatus serverStatus, Models::Rooms rooms) {
    this->rooms = rooms;

    for(auto &room : this->rooms){
        this->createRoomItem(room);
        connect(roomsItems[room.localID], SIGNAL(switchToRoom(int,QString)), this, SLOT(switchToRoom(int,QString)));
    }
}

void RoomsList::clearContents() {
    for (auto &room : rooms) {
        roomsItems[room.localID]->deleteLater();
    }

    rooms.clear();
    roomsItems.clear();
}

void RoomsList::createRoomItem(Models::Room &room) {
    auto item = qobject_cast<QQuickItem*>(itemComponent->create(engine->rootContext()));

    item->setProperty("roomName", room.name);
    item->setProperty("roomCreatorName", room.creatorName);
    item->setProperty("roomCreatorID", QString::number(room.creatorID));

    item->setParentItem(roomContainer);
    roomsItems[room.localID] = item;
}

void RoomsList::sortBy(QString by, bool ascending) {
    for (auto &room : rooms) {
        roomsItems[room.localID]->setParentItem(nullptr);
    }

    auto get_str = [&by](Models::Room room) { return (room.property(by.toStdString().c_str())).toString().toLower().trimmed(); };

    std::stable_sort(rooms.begin(), rooms.end(),
                     [&ascending, &by, &get_str](const Models::Room r1, const Models::Room r2) {
        QString s1 = get_str(r1), s2 = get_str(r2);
        return (ascending && s1 < s2) || (!ascending && s1 > s2);
    });

    for(auto &room : rooms) {
        roomsItems[room.localID]->setParentItem(roomContainer);
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
