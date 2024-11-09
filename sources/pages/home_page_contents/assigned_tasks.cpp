#include "assigned_tasks.h"

AssignedTasks::AssignedTasks(QQmlEngine *engine, QQuickItem *container, HomePage *homePage) :
        TasksList(engine, container, homePage) {
    connect(netManager, &NetworkManager::finishGetProfileAssignedTasksResponseHandling, this, &TasksList::tasksInitialization);

    netManager->sendGetProfileAssignedTasksRequest();
}

AssignedTasks::~AssignedTasks() {}
