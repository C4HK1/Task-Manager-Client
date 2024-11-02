#include <nlohmann/json.hpp>

#include "room_page.h"
#include "main_page.h"
#include "task_creation_form.h"

//Object part
RoomPage::RoomPage(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage, Room room) :
        BasePage(engine, container, "qml/Room.qml"),
        taskComponent(new QQmlComponent(engine, "qml/Task.qml")),
        tasksContainer(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("tasksContainer")),
        mainPage(mainPage),
        room(room) {
    object->setProperty("roomName", room.name);
    object->setProperty("roomCreatorName", room.creatorName);
    object->setProperty("roomCreatorID", std::to_string(room.creatorID).c_str());

    connect(netManager, &NetworkManager::finishGetRoomTasksResponseHandling, this, &RoomPage::roomPageInitialization);
    connect(this->getObject(), SIGNAL(switchToTaskCreationForm()), this, SLOT(switchToTaskCreationForm()));

    netManager->sendGetRoomTasksRequest(room.creatorID, room.name);
}

RoomPage::~RoomPage() {
    taskComponent->deleteLater();
}


//Methods
void RoomPage::addTask(Task task) {
    tasks.append(task);

    auto item = qobject_cast<QQuickItem*>(taskComponent->create(engine->rootContext()));
    item->setProperty("roomCreatorID", QString::number(task.parent.creatorID));
    item->setProperty("roomName", task.parent.name);
    item->setProperty("taskName", task.name);
    item->setProperty("taskCreatorID", QString::number(task.creatorID));
    item->setProperty("taskCreatorName", task.creatorName);
    item->setParentItem(tasksContainer);
}

//Form part
void RoomPage::setCurrentForm(BasePage *form){
    if (curForm != nullptr) {
        curForm->deleteLater();
    }

    curForm = form;
}

template <typename FormType, typename ...Args> requires IsPage<FormType>
void RoomPage::switchForm(Args... args) {
    setCurrentForm(new FormType(engine, this->getObject(), this, args...));
}

void RoomPage::closeForm() {
    setCurrentForm(nullptr);
}


//Slots part
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

//Switchers
void RoomPage::switchToTaskCreationForm() { switchForm<TaskCreationForm>(); }
