#include "reviewed_tasks.h"

ReviewedTasks::ReviewedTasks(QQmlEngine *engine, HomePage *homePage) :
    TasksList(engine, homePage) { }

ReviewedTasks::~ReviewedTasks() {}

void ReviewedTasks::update() {
    connect(netManager, &NetworkManager::finishGetProfileReviewedTasksResponseHandling, this, &TasksList::tasksInitialization);
    netManager->sendGetProfileReviewedTasksRequest();
}

void ReviewedTasks::leave() {
    disconnect(netManager, &NetworkManager::finishGetProfileReviewedTasksResponseHandling, this, &TasksList::tasksInitialization);
    clearContents();
}
