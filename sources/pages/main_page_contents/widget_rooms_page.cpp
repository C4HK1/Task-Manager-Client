#include "widget_rooms_page.h"

WidgetRoomsPage::WidgetRoomsPage(QQmlEngine *engine, QQuickItem *container) :
    RoomsPage(engine, container, "qml/WidgetRooms.qml", "qml/MainWorkspaceElements/RoomWidget.qml"),
    widget_container(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("widget_container"))
{}

void WidgetRoomsPage::createRoomItem(RoomInfo *ri) {
    auto item = qobject_cast<QQuickItem*>(item_component->create(engine->rootContext()));
    item->findChild<QQuickItem*>("room_name")->setProperty("text", ri->room_name);
    item->findChild<QQuickItem*>("owner_name")->setProperty("text", ri->owner_name);

    ri->room_item = item;
    item->setParentItem(widget_container);
    rooms_items.append(item);
}
