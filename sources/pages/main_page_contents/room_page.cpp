#include <nlohmann/json.hpp>

#include "room_page.h"

RoomPage::RoomPage(QQmlEngine *engine, QQuickItem *container, RoomInfo *room, NetworkManager *net_manager) :
    BasePage(engine, container, "qml/Room.qml"),
    task_component(new QQmlComponent(engine, "qml/Task.qml")),
    net_manager(net_manager),
    room(room),
    tasks_container(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("tasks_container"))
{
    qInfo() << room->room_name << room->owner_name << room->owner_id;
    object->setProperty("room_name", room->room_name);
    object->setProperty("owner_name", room->owner_name);
    object->setProperty("owner_id", room->owner_id);

    connect(net_manager, &NetworkManager::gotTasks, this, &RoomPage::loadTasks);
    connect(net_manager, &NetworkManager::gotTask, this, &RoomPage::loadTask);
    net_manager->sendGettingRoomTasksRequest(*room);
}

void RoomPage::loadTasks(QList<TaskInfo *> tasks) {
    for (auto task : tasks) {
        auto item = qobject_cast<QQuickItem*>(task_component->create(engine->rootContext()));
        item->findChild<QQuickItem*>("task_name")->setProperty("text", task->task_name);
        item->findChild<QQuickItem*>("owner_name")->setProperty("text", task->owner_name);
        item->setParentItem(tasks_container);
    }
}

void RoomPage::loadTask(bool status) {
    if (status) {
        // QMetaObject::invokeMethod(object, "taskCreated");
    } else {
        // QMetaObject::invokeMethod(object, "taskCreationFailed");
    }
}

RoomPage::~RoomPage() {
    delete room;
}
