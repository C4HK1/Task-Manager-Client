#include "list_rooms_page.h"

ListRoomsPage::ListRoomsPage(QQmlEngine *engine, QQuickItem *container) :
    RoomsPage(engine, container, "ListRooms.qml", "MainWorkspaceElements/RoomListItem.qml") {}

void ListRoomsPage::AddRoom(RoomInfo *ri) {}
