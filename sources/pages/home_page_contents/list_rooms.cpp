#include "list_rooms.h"

//Object part
ListRooms::ListRooms(QQmlEngine *engine, QQuickItem *container, HomePage *homePage) :
        RoomsList(engine, container, "qml/ListRooms.qml", "qml/MainWorkspaceElements/RoomListItem.qml", homePage),
        listContainer(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("listContainer")) {
}

ListRooms::~ListRooms() {
}


//Slots
void ListRooms::createRoomItem(Models::Room &room) {
    auto item = qobject_cast<QQuickItem*>(itemComponent->create(engine->rootContext()));
    item->setProperty("roomName", room.name);
    item->setProperty("roomCreatorName", room.creatorName);
    item->setProperty("roomCreatorID", QString::number(room.creatorID));

    room.roomItem = item;
    item->setParentItem(listContainer);
    roomsItems.append(item);
}
