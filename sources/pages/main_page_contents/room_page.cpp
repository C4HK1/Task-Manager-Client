#include <nlohmann/json.hpp>

#include "room_page.h"

RoomPage::RoomPage(QQmlEngine *engine, QQuickItem *container, RoomInfo *room, NetworkManager *net_manager) :
    BasePage(engine, container, "qml/Room.qml"),
    task_component(new QQmlComponent(engine, "qml/Task.qml")),
    net_manager(net_manager),
    room(room),
    tasks_container(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("tasks_container"))
{
    object->setProperty("room_name", room->room_name);
    object->setProperty("owner_name", room->owner_name);
    object->setProperty("owner_id", room->owner_id);

    connect(net_manager, &NetworkManager::gotTasks, this, &RoomPage::loadTasks);
    connect(net_manager, &NetworkManager::gotTask, this, &RoomPage::loadTask);
    connect(net_manager, &NetworkManager::taskCreationFailed, this, &RoomPage::taskCreationFailed);
    net_manager->sendGettingRoomTasksRequest(*room);
}

void RoomPage::loadTasks(QList<TaskInfo *> tasks) {
    this->tasks = tasks;

    for (auto task : this->tasks) {
        auto item = qobject_cast<QQuickItem*>(task_component->create(engine->rootContext()));
        item->setProperty("task_name", task->task_name);
        item->setProperty("owner_name", task->owner_name);
        item->setProperty("owner_id", task->owner_id);
        item->setProperty("room_id", task->room_id);
        item->setParentItem(tasks_container);
    }
}

void RoomPage::loadTask(TaskInfo *task) {
    tasks.append(task);

    auto item = qobject_cast<QQuickItem*>(task_component->create(engine->rootContext()));
    item->setProperty("task_name", task->task_name);
    item->setProperty("owner_name", task->owner_name);
    item->setProperty("owner_id", task->owner_id);
    item->setProperty("room_id", task->room_id);
    item->setParentItem(tasks_container);

    QMetaObject::invokeMethod(object, "taskCreated");
}

void RoomPage::taskCreationFailed() {
    QMetaObject::invokeMethod(object, "taskCreationFailed");
}

RoomPage::~RoomPage() {
    // delete room;

    // for (auto task : tasks) {
    //     delete task;
    // }
}
