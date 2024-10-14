#include "list_rooms_page.h"

ListRoomsPage::ListRoomsPage(QQmlEngine *engine, QQuickItem *container) :
    RoomsPage(engine, container, "qml/ListRooms.qml", "qml/MainWorkspaceElements/RoomListItem.qml"),
    list_container(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("list_container"))
{}

void ListRoomsPage::createRoomItem(RoomInfo *ri) {
    auto item = qobject_cast<QQuickItem*>(item_component->create(engine->rootContext()));
    item->findChild<QQuickItem*>("room_name")->setProperty("text", ri->room_name);
    item->findChild<QQuickItem*>("owner_name")->setProperty("text", ri->owner_name);
    item->setProperty("owner_id", ri->owner_id);

    ri->room_item = item;
    item->setParentItem(list_container);
    rooms_items.append(item);
}
