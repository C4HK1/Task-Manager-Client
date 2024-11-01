#include <nlohmann/json.hpp>

#include "task_creation_page.h"
#include "main_page.h"

TaskCreationPage::TaskCreationPage(QQmlEngine *engine, QQuickItem *container) :
        BasePage(engine, container, "qml/TaskCreation.qml") {
    connect(netManager, &NetworkManager::finishCreateTaskResponseHandling, this, &TaskCreationPage::finishCreateTask);
    connect(this->getObject(), SIGNAL(createTask(int, QString, QString, QString, QString, int, int)), this, SLOT(createTask(int, QString, QString, QString, QString, int, int)));
}

void TaskCreationPage::createTask(int roomCreatorID,
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

void TaskCreationPage::finishCreateTask(ServerStatus serverStatus, Task task) {
    if (!serverStatus.status) {
        qInfo() << "close";
        emit closeTaskCreatiornForm();
    } else {
        qInfo() << "error task creation with status: " << serverStatus.status;
    }
}

TaskCreationPage::~TaskCreationPage() {}
