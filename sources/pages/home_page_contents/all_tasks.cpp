#include "all_tasks.h"

AllTasks::AllTasks(QQmlEngine *engine, HomePage *homePage) :
        TasksList(engine, homePage) {}

AllTasks::~AllTasks() {}

void AllTasks::update() {
    connect(netManager, &NetworkManager::finishGetProfileTasksResponseHandling, this, &TasksList::tasksInitialization);
    netManager->sendGetProfileTasksRequest();
}

void AllTasks::leave() {
    disconnect(netManager, &NetworkManager::finishGetProfileTasksResponseHandling, this, &TasksList::tasksInitialization);
    clearContents();
}
