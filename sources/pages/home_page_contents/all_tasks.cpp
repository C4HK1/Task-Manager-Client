#include "all_tasks.h"

AllTasks::AllTasks(QQmlEngine *engine, HomePage *homePage) :
        TasksList(engine, homePage) {
    connect(netManager, &NetworkManager::finishGetProfileTasksResponseHandling, this, &TasksList::tasksInitialization);

    netManager->sendGetProfileTasksRequest();
}

AllTasks::~AllTasks() {}
