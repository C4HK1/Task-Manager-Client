#include "assigned_tasks.h"

AssignedTasks::AssignedTasks(QQmlEngine *engine, HomePage *homePage) :
        TasksList(engine, homePage) {
    connect(netManager, &NetworkManager::finishGetProfileAssignedTasksResponseHandling, this, &TasksList::tasksInitialization);

    netManager->sendGetProfileAssignedTasksRequest();
}

AssignedTasks::~AssignedTasks() {}
