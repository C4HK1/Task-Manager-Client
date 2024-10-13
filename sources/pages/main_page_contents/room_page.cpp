#include <nlohmann/json.hpp>

#include "room_page.h"

RoomPage::RoomPage(QQmlEngine *engine, QQuickItem *container, RoomInfo *room, NetworkManager *net_manager) :
    BasePage(engine, container, "qml/Room.qml"),
    task_component(new QQmlComponent(engine, "qml/MainWorkspaceElements/Task.qml")),
    net_manager(net_manager),
    room(room),
    tasks_container(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("tasks_container"))
{
    connect(net_manager, &NetworkManager::gotTasks, this, &RoomPage::loadTasks);
}

void RoomPage::loadTasks(QList<TaskInfo *> tasks) {
    for (auto task : tasks) {
        auto item = qobject_cast<QQuickItem*>(task_component->create(engine->rootContext()));
        item->findChild<QQuickItem*>("room_name")->setProperty("text", task->task_name);
        item->findChild<QQuickItem*>("owner_name")->setProperty("text", task->owner_name);
        item->setParentItem(tasks_container);
    }
}

RoomPage::~RoomPage() {
    delete room;
}
