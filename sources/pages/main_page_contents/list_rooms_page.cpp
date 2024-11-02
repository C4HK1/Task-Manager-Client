#include "list_rooms_page.h"

ListRoomsPage::ListRoomsPage(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage) :
        RoomsPage(engine, container, "qml/ListRooms.qml", "qml/MainWorkspaceElements/RoomListItem.qml", mainPage),
        listContainer(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("listContainer")),
        mainPage(mainPage) {
}

void ListRoomsPage::createRoomItem(Room &room) {
    auto item = qobject_cast<QQuickItem*>(itemComponent->create(engine->rootContext()));
    item->setProperty("roomName", room.name);
    item->setProperty("roomCreatorName", room.creatorName);
    item->setProperty("roomCreatorID", QString::number(room.creatorID));

    room.roomItem = item;
    item->setParentItem(listContainer);
    roomsItems.append(item);
}
