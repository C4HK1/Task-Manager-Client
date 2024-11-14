#include "widget_rooms.h"

//Object part
WidgetRooms::WidgetRooms(QQmlEngine *engine, HomePage *homePage) :
    RoomsList(engine, "qml/WidgetRooms.qml", "qml/MainWorkspaceElements/RoomWidget.qml", homePage),
    widgetContainer(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("widgetContainer")) {
}

WidgetRooms::~WidgetRooms() {
}


//Slots
void WidgetRooms::createRoomItem(Models::Room &room) {
    auto item = qobject_cast<QQuickItem*>(itemComponent->create(engine->rootContext()));

    item->setProperty("roomName", room.name);
    item->setProperty("roomCreatorName", room.creatorName);
    item->setProperty("roomCreatorID", QString::number(room.creatorID));

    item->setParentItem(widgetContainer);
    roomsItems[room.localID] = item;
}
