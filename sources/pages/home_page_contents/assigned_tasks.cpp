#include "assigned_tasks.h"

AssignedTasks::AssignedTasks(QQmlEngine *engine, HomePage *homePage) :
        TasksList(engine, homePage) { }

AssignedTasks::~AssignedTasks() {}

void AssignedTasks::update() {
    connect(netManager, &NetworkManager::finishGetProfileAssignedTasksResponseHandling, this, &TasksList::tasksInitialization);
    netManager->sendGetProfileAssignedTasksRequest();
}

void AssignedTasks::leave() {
    disconnect(netManager, &NetworkManager::finishGetProfileAssignedTasksResponseHandling, this, &TasksList::tasksInitialization);
    clearContents();
}
