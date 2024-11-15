#include "widget_rooms.h"

//Object part
WidgetRooms::WidgetRooms(QQmlEngine *engine, HomePage *homePage) :
    RoomsList(engine, "qml/WidgetRooms.qml", "qml/MainWorkspaceElements/RoomWidget.qml", homePage)
{
    roomContainer = object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("widgetContainer");
}

WidgetRooms::~WidgetRooms() {}
