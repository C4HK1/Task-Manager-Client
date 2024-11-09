#include "reviewed_tasks.h"

ReviewedTasks::ReviewedTasks(QQmlEngine *engine, QQuickItem *container, HomePage *homePage) :
    TasksList(engine, container, homePage) {
    connect(netManager, &NetworkManager::finishGetProfileReviewedTasksResponseHandling, this, &TasksList::tasksInitialization);

    netManager->sendGetProfileReviewedTasksRequest();
}

ReviewedTasks::~ReviewedTasks() {}
