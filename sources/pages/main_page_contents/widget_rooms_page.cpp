#include "widget_rooms_page.h"

WidgetRoomsPage::WidgetRoomsPage(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage) :
    RoomsPage(engine, container, "qml/WidgetRooms.qml", "qml/MainWorkspaceElements/RoomWidget.qml", mainPage),
    widgetContainer(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("widgetContainer")) {
}

void WidgetRoomsPage::createRoomItem(Room &room) {
    auto item = qobject_cast<QQuickItem*>(itemComponent->create(engine->rootContext()));
    item->setProperty("roomName", room.name);
    item->setProperty("roomCreatorName", room.creatorName);
    item->setProperty("roomCreatorID", QString::number(room.creatorID));

    room.roomItem = item;
    item->setParentItem(widgetContainer);
    roomsItems.append(item);
}
