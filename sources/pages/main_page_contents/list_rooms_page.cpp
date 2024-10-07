#include "list_rooms_page.h"

ListRoomsPage::ListRoomsPage(QQmlEngine *engine, QQuickItem *container) :
    RoomsPage(engine, container, "qml/ListRooms.qml", "qml/MainWorkspaceElements/RoomListItem.qml") {}

void ListRoomsPage::AddRoom(RoomInfo *ri) {}
