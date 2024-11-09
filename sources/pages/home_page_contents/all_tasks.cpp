#include "all_tasks.h"

AllTasks::AllTasks(QQmlEngine *engine, QQuickItem *container, HomePage *homePage) :
        TasksList(engine, container, homePage) {
    connect(netManager, &NetworkManager::finishGetProfileTasksResponseHandling, this, &TasksList::tasksInitialization);

    netManager->sendGetProfileTasksRequest();
}

AllTasks::~AllTasks() {}
