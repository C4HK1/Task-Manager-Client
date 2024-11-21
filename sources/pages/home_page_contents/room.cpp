#include <nlohmann/json.hpp>

#include "room.h"
#include "home_page.h"
#include "task_creation_form.h"
#include "invitation_form.h"

//Object part
Room::Room(QQmlEngine *engine, HomePage *homePage, Models::Room room) :
        BasePage(engine, "qml/Room.qml"),
        taskComponent(new QQmlComponent(engine, "qml/Task.qml")),
        tasksContainer(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("tasksContainer")),
        homePage(homePage),
        room(room) {
    object->setProperty("roomName", room.name);
    object->setProperty("roomCreatorName", room.creatorName);
    object->setProperty("roomCreatorID", QString::number(room.creatorID));

    connect(this->getObject(), SIGNAL(switchToTaskCreationForm()), this, SLOT(switchToTaskCreationForm()));
    connect(this->getObject(), SIGNAL(switchToInvitationForm()), this, SLOT(switchToInvitationForm()));
    connect(this->getObject(), SIGNAL(leaveFormRoom(int, QString)), this, SLOT(leaveFormRoom(int, QString)));
}

Room::~Room() {
    clearContents();
    taskComponent->deleteLater();
}

void Room::update() {
    connect(netManager, &NetworkManager::finishGetRoomTasksResponseHandling, this, &Room::setTasks);
    connect(netManager, &NetworkManager::finishLeaveFromRoomResponseHandling, this, &Room::finishLeaveFromRoom);
    netManager->sendGetRoomTasksRequest(room.creatorID, room.name);
}

void Room::leave() {
    disconnect(netManager, &NetworkManager::finishGetRoomTasksResponseHandling, this, &Room::setTasks);
    disconnect(netManager, &NetworkManager::finishLeaveFromRoomResponseHandling, this, &Room::finishLeaveFromRoom);
    clearContents();
}

void Room::clearContents() {
    for(auto &task : tasks) {
        tasksItems[task.localID]->deleteLater();
    }

    tasks.clear();
    tasksItems.clear();
}


//Methods
void Room::addTask(Models::Task task) {
    tasks.append(task);

    auto item = qobject_cast<QQuickItem*>(taskComponent->create(engine->rootContext()));
    item->setProperty("roomCreatorID", QString::number(task.parent.creatorID));
    item->setProperty("roomName", task.parent.name);
    item->setProperty("taskName", task.name);
    item->setProperty("taskLocalID", (int) task.localID);
    item->setProperty("taskCreatorID", QString::number(task.creatorID));
    item->setProperty("taskCreatorName", task.creatorName);

    connect(item, SIGNAL(switchToTaskForm(int)), this, SLOT(switchToTaskForm(int)));

    item->setParentItem(tasksContainer);
    tasksItems[task.localID] = item;
}

//Form part
void Room::setCurrentForm(BaseElement *form){
    if (curForm != nullptr) {
        curForm->deleteLater();
    }

    curForm = form;

    if(curForm != nullptr) {
        connect(curForm->getObject(), SIGNAL(closeForm()), this, SLOT(closeForm()));
    }
}

template <typename FormType, typename ...Args> requires IsElement<FormType>
void Room::switchForm(Args... args) {
    setCurrentForm(new FormType(engine, this->getObject(), this, args...));
}

//Slots part
void Room::setTasks(Models::ServerStatus serverStatus, Models::Tasks tasks) {
    if (!serverStatus.status) {
        this->tasks = tasks;

        for (auto &task : this->tasks) {
            auto item = qobject_cast<QQuickItem*>(taskComponent->create(engine->rootContext()));
            item->setProperty("roomCreatorID", QString::number(task.parent.creatorID));
            item->setProperty("roomName", task.parent.name);
            item->setProperty("taskLocalID", (int) task.localID);
            item->setProperty("taskName", task.name);
            item->setProperty("taskCreatorID", std::to_string(task.creatorID).c_str());
            item->setProperty("taskCreatorName", task.creatorName);

            connect(item, SIGNAL(switchToTaskForm(int)), this, SLOT(switchToTaskForm(int)));

            item->setParentItem(tasksContainer);
            tasksItems[task.localID] = item;
        }
    } else {
        qInfo() << "error get room tasks status: " << serverStatus.status;
    }
}

void Room::leaveFormRoom(int roomCreatorID, QString roomName) {
    this->netManager->sendLeaveFromRoomRequest(roomCreatorID, roomName);
}

void Room::finishLeaveFromRoom(Models::ServerStatus serverStatus) {
    if (!serverStatus.status) {
        this->homePage->switchToWidgetRooms();
    } else {
        qInfo() << "error leave from room with status: " << serverStatus.status;
    }
}

//Switchers
void Room::switchToTaskCreationForm() { switchForm<TaskCreationForm>(); }
void Room::switchToInvitationForm() { switchForm<InvitationForm>(); }
void Room::switchToTaskForm(int localID) {
    for(auto &task : tasks) {
        if (task.localID == localID) {
            switchForm<TaskForm>(&task);
            break;
        }
    }
}

void Room::closeForm() {
    setCurrentForm(nullptr);
}

