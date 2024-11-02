#include <nlohmann/json.hpp>

#include "task_creation_form.h"
#include "room_page.h"

TaskCreationForm::TaskCreationForm(QQmlEngine *engine, QQuickItem *container, RoomPage *roomPage) :
        BasePage(engine, container, "qml/TaskCreation.qml"),
        roomPage(roomPage) {
    connect(this->getObject(), SIGNAL(createTask(int, QString, QString, QString, QString, int, int)), this, SLOT(createTask(int, QString, QString, QString, QString, int, int)));
    connect(this->getObject(), SIGNAL(closeTaskCreationForm()), this, SLOT(closeTaskCreationForm()));

    connect(netManager, &NetworkManager::finishCreateTaskResponseHandling, this, &TaskCreationForm::finishCreateTask);
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
    this->roomPage->closeForm();
}

void TaskCreationForm::finishCreateTask(ServerStatus serverStatus, Task task) {
    if (!serverStatus.status) {
        qInfo() << "close";
        this->roomPage->addTask(task);
        this->roomPage->closeForm();
    } else {
        qInfo() << "error task creation with status: " << serverStatus.status;
    }
}

TaskCreationForm::~TaskCreationForm() {}
