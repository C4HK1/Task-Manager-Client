#include "reviewed_tasks.h"

ReviewedTasks::ReviewedTasks(QQmlEngine *engine, HomePage *homePage) :
    TasksList(engine, homePage) {
    connect(netManager, &NetworkManager::finishGetProfileReviewedTasksResponseHandling, this, &TasksList::tasksInitialization);

    netManager->sendGetProfileReviewedTasksRequest();
}

ReviewedTasks::~ReviewedTasks() {}
