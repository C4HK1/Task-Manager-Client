#include "tasks_list.h"
#include "network_manager.h"
#include "home_page.h"

//Object part
TasksList::TasksList(QQmlEngine *engine, QQuickItem *container, HomePage *homePage) :
        BaseElement(engine, container, "qml/Tasks.qml"),
        itemComponent(new QQmlComponent(engine, QUrl::fromLocalFile("qml/MainWorkspaceElements/TaskListItem.qml"))),
        listContainer(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("listContainer")),
        homePage(homePage) {
    connect(object, SIGNAL(sortBy(QString,bool)), this, SLOT(sortBy(QString,bool)));
    connect(netManager, &NetworkManager::finishGetProfileTasksResponseHandling, this, &TasksList::tasksInitialization);

    netManager->sendGetProfileTasksRequest();
}

TasksList::~TasksList(){
    for(auto &task : tasks) {
        task.taskItem->deleteLater();
        task.taskItem = nullptr;
    }

    itemComponent->deleteLater();
}


//Slots
void TasksList::sortBy(QString by, bool ascending) {
    for (auto &task : tasks) {
        task.taskItem->setParentItem(nullptr);
    }

    auto get_str = [&by](Models::Task task) { return (task.property(by.toStdString().c_str())).toString().toLower().trimmed(); };

    std::sort(tasks.begin(), tasks.end(),
              [&ascending, &by, &get_str](Models::Task t1, Models::Task t2) { return (get_str(t1) < get_str(t2)) ^ !ascending; });

    for(auto &task : tasks) {
        task.taskItem->setParentItem(listContainer);
    }
}

void TasksList::tasksInitialization(Models::ServerStatus serverStatus, Models::Tasks tasks) {
    if (!serverStatus.status) {
        this->tasks = tasks;

        for(auto &task : this->tasks){
            this->createTaskItem(task);
            connect(task.taskItem, SIGNAL(openRoom(int, QString)), this, SLOT(openRoom(int, QString)));
        }

        this->sortBy("taskName", true);
    } else {
        qInfo() << "get profile room error status: " << serverStatus.status;
    }
}

void TasksList::openRoom(int roomCreatorID, QString roomName) {
    for (auto &task : this->tasks) {    // REIMPLEMENTATION REQUIRED
        if (task.parent.creatorID == roomCreatorID && task.parent.name == roomName) {
            this->homePage->switchToRoom(task.parent);
            break;
        }
    }
}

//Methods
void TasksList::createTaskItem(Models::Task &task){
    auto item = qobject_cast<QQuickItem*>(itemComponent->create(engine->rootContext()));

    item->setProperty("roomCreatorID", QString::number(task.parent.creatorID));
    item->setProperty("roomName", task.parent.name);
    item->setProperty("taskName", task.name);

    task.taskItem = item;
    item->setParentItem(listContainer);
}
