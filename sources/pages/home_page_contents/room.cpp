#include <nlohmann/json.hpp>

#include "room.h"
#include "home_page.h"
#include "task_creation_form.h"
#include "invitation_form.h"

//Object part
Room::Room(QQmlEngine *engine, QQuickItem *container, HomePage *homePage, Models::Room room) :
        BaseElement(engine, container, "qml/Room.qml"),
        taskComponent(new QQmlComponent(engine, "qml/Task.qml")),
        tasksContainer(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("tasksContainer")),
        homePage(homePage),
        room(room) {
    object->setProperty("roomName", room.name);
    object->setProperty("roomCreatorName", room.creatorName);
    object->setProperty("roomCreatorID", QString::number(room.creatorID));

    connect(netManager, &NetworkManager::finishGetRoomTasksResponseHandling, this, &Room::setTasks);
    connect(this->getObject(), SIGNAL(switchToTaskCreationForm()), this, SLOT(switchToTaskCreationForm()));
    connect(this->getObject(), SIGNAL(switchToInvitationForm()), this, SLOT(switchToInvitationForm()));

    netManager->sendGetRoomTasksRequest(room.creatorID, room.name);
}

Room::~Room() {
    taskComponent->deleteLater();
}


//Methods
void Room::addTask(Models::Task task) {
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
void Room::setCurrentForm(BaseElement *form){
    if (curForm != nullptr) {
        curForm->deleteLater();
    }

    curForm = form;
}

template <typename FormType, typename ...Args> requires IsElement<FormType>
void Room::switchForm(Args... args) {
    setCurrentForm(new FormType(engine, this->getObject(), this, args...));
}

void Room::closeForm() {
    setCurrentForm(nullptr);
}


//Slots part
void Room::setTasks(Models::ServerStatus serverStatus, Models::Tasks tasks) {
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
void Room::switchToTaskCreationForm() { switchForm<TaskCreationForm>(); }
void Room::switchToInvitationForm() { switchForm<InvitationForm>(); }
