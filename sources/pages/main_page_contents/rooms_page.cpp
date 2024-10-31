#include "rooms_page.h"
#include "main_page.h"

RoomsPage::RoomsPage(QQmlEngine *engine, QQuickItem *container, QString moduleName, QString itemName, MainPage *mainPage) :
        BasePage(engine, container, moduleName), itemComponent(new QQmlComponent(engine, QUrl::fromLocalFile(itemName))),
        mainPage(mainPage) {
    connect(this->getObject(), SIGNAL(switchToRoomCreation()), this, SLOT(switchToRoomCreation()));

    connect(netManager, &NetworkManager::finishGetProfileRoomsResponseHandling, this, &RoomsPage::initializeContents);
    netManager->sendGetProfileRoomsRequest();

    connect(netManager, &NetworkManager::finishGetRoomResponseHandling, this, &RoomsPage::handleRoomEntry);
}

void RoomsPage::initializeContents(ServerStatus serverStatus, Rooms rooms) {
    this->rooms = rooms;

    for(auto &room : this->rooms){
        this->createRoomItem(room);
    }
}

void RoomsPage::switchToRoomCreation() {
    this->mainPage->switchToRoomCreation();
}

void RoomsPage::handleRoomEntry(ServerStatus serverStatus, Room room) {
    if (!serverStatus.status) {
        this->mainPage->switchToRoom(room);
    } else {
        qInfo() << "error room entry with status: " << serverStatus.status;
    }
}

RoomsPage::~RoomsPage(){
    for(auto &item : roomsItems) {
        item->deleteLater();
    }

    itemComponent->deleteLater();
}
