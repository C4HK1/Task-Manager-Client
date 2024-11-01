#include <nlohmann/json.hpp>

#include "room_page.h"

RoomPage::RoomPage(QQmlEngine *engine, QQuickItem *container, Room room) :
        BasePage(engine, container, "qml/Room.qml"),
        taskComponent(new QQmlComponent(engine, "qml/Task.qml")),
        tasksContainer(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("tasksContainer")),
        room(room) {
    object->setProperty("roomName", room.name);
    object->setProperty("roomCreatorName", room.creatorName);
    object->setProperty("roomCreatorID", std::to_string(room.creatorID).c_str());

    connect(netManager, &NetworkManager::finishGetRoomTasksResponseHandling, this, &RoomPage::roomPageInitialization);
    connect(netManager, &NetworkManager::finishCreateTaskResponseHandling, this, &RoomPage::handleTaskCreationStatus);

    connect(this->getObject(), SIGNAL(openTaskCreationForm()), this, SLOT(openTaskCreationForm()));
    netManager->sendGetRoomTasksRequest(room.creatorID, room.name);
}

void RoomPage::openTaskCreationForm() {
    emit switchToTaskCreation();
}

void RoomPage::roomPageInitialization(ServerStatus serverStatus, Tasks tasks) {
    if (!serverStatus.status) {
        this->tasks = tasks;

        for (auto task : this->tasks) {
            auto item = qobject_cast<QQuickItem*>(taskComponent->create(engine->rootContext()));
            item->setProperty("roomCreatorID", QString::number(task.parent.creatorID));
            item->setProperty("roomName", task.parent.name);
            item->setProperty("taskName", task.name);
            item->setProperty("taskCreatorID", std::to_string(task.creatorID).c_str());
            item->setProperty("taskCreatorName", task.creatorName);

            item->setParentItem(tasksContainer);
        }
    } else {
        qInfo() << "error get room tasks status: " << serverStatus.status;
    }
}

void RoomPage::handleTaskCreationStatus(ServerStatus serverStatus, Task task) {
    if (!serverStatus.status) {
        tasks.append(task);

        auto item = qobject_cast<QQuickItem*>(taskComponent->create(engine->rootContext()));
        item->setProperty("roomCreatorID", QString::number(task.parent.creatorID));
        item->setProperty("roomName", task.parent.name);
        item->setProperty("taskName", task.name);
        item->setProperty("taskCreatorID", QString::number(task.creatorID));
        item->setProperty("taskCreatorName", task.creatorName);
        item->setParentItem(tasksContainer);
    }
}

RoomPage::~RoomPage() {
    taskComponent->deleteLater();
}
