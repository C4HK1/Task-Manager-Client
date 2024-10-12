#include <nlohmann/json.hpp>

#include "room_page.h"

RoomPage::RoomPage(QQmlEngine *engine, QQuickItem *container, RoomInfo *room, NetworkManager *net_manager) : BasePage(engine, container, "qml/Room.qml"), net_manager(net_manager), room(room) {
    connect(net_manager, &NetworkManager::gotTasks, this, &RoomPage::loadTasks);
}

void RoomPage::loadTasks(QList<TaskInfo *> tasks) {
    for (auto i : tasks) {
        qInfo() << i;
    }
}

RoomPage::~RoomPage() {
    delete room;
}
