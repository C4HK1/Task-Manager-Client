#include <nlohmann/json.hpp>

#include "room_creation_page.h"

RoomCreationPage::RoomCreationPage(QQmlEngine *engine, QQuickItem *container) :
    BasePage(engine, container, "qml/RoomCreation.qml")
{
    connect(net_manager, &NetworkManager::roomCreationFailed, this, &RoomCreationPage::loadFailInfo);
}

void RoomCreationPage::loadFailInfo() {
    QMetaObject::invokeMethod(object, "roomCreationFailed");
}

RoomCreationPage::~RoomCreationPage() {}
