#include "list_rooms.h"

//Object part
ListRooms::ListRooms(QQmlEngine *engine, HomePage *homePage) :
        RoomsList(engine, "qml/ListRooms.qml", "qml/MainWorkspaceElements/RoomListItem.qml", homePage)
{
    roomContainer = object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("listContainer");
}

ListRooms::~ListRooms() {}
