#include "widget_rooms_page.h"

WidgetRoomsPage::WidgetRoomsPage(QQmlEngine *engine, QQuickItem *container) :
    RoomsPage(engine, container, "qml/WidgetRooms.qml", "qml/MainWorkspaceElements/RoomWidget.qml") {}

void WidgetRoomsPage::AddRoom(RoomInfo *ri) {}
