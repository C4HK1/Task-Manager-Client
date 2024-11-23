#include <nlohmann/json.hpp>

#include "task_creation_form.h"
#include "room.h"

//Object part
TaskCreationForm::TaskCreationForm(QQmlEngine *engine, QQuickItem *parent, Room *room) :
        BaseForm(engine, parent, "qml/TaskCreation.qml"),
        room(room) {
    connect(this->getObject(), SIGNAL(createTask(int, QString, QString, QString, QString, int, int)), this, SLOT(createTask(int, QString, QString, QString, QString, int, int)));
    connect(this->getObject(), SIGNAL(closeTaskCreationForm()), this, SLOT(closeTaskCreationForm()));

    connect(netManager, &NetworkManager::finishCreateTaskResponseHandling, this, &TaskCreationForm::finishCreateTask);
}

TaskCreationForm::~TaskCreationForm() {
}


//Slots
void TaskCreationForm::createTask(int roomCreatorID,
                                  QString roomName,
                                  QString taskName,
                                  QString description,
                                  QString label,
                                  int status,
                                  int timeToLive) {
    this->netManager->sendCreateTaskRequest(roomCreatorID,
                                            roomName,
                                            taskName,
                                            description,
                                            label,
                                            status,
                                            timeToLive);
}

void TaskCreationForm::closeTaskCreationForm() {
    this->room->closeForm();
}

void TaskCreationForm::finishCreateTask(Models::ServerStatus serverStatus, Models::Task task) {
    if (!serverStatus.status) {
        qInfo() << "close";
        this->room->addTask(task);
        this->room->closeForm();
    } else {
        qInfo() << "error task creation with status: " << serverStatus.status;
    }
}
