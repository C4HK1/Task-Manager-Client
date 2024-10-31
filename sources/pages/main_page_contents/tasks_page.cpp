#include "tasks_page.h"
#include "network_manager.h"
#include "main_page.h"

TasksPage::TasksPage(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage) :
        BasePage(engine, container, "qml/Tasks.qml"),
        itemComponent(new QQmlComponent(engine, QUrl::fromLocalFile("qml/MainWorkspaceElements/TaskListItem.qml"))),
        listContainer(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("listContainer")),
        mainPage(mainPage) {
    connect(object, SIGNAL(sortBy(QString,bool)), this, SLOT(sortBy(QString,bool)));
    connect(netManager, &NetworkManager::finishGetProfileTasksResponseHandling, this, &TasksPage::tasksInitialization);
    netManager->sendGetProfileTasksRequest();
}

void TasksPage::tasksInitialization(ServerStatus serverStatus, Tasks tasks) {
    qInfo() << "test";

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

void TasksPage::openRoom(int roomCreatorID, QString roomName) {
    for (auto &task : this->tasks) {    // REIMPLEMENTATION REQUIRED
        if (task.parent.creatorID == roomCreatorID && task.parent.name == roomName) {
            mainPage->switchToRoom(task.parent);
            break;
        }
    }
}

void TasksPage::createTaskItem(Task &task){
    auto item = qobject_cast<QQuickItem*>(itemComponent->create(engine->rootContext()));
    item->setProperty("roomCreatorID", QString::number(task.parent.creatorID));
    item->findChild<QQuickItem*>("roomName")->setProperty("text", task.parent.name);
    item->findChild<QQuickItem*>("taskName")->setProperty("text", task.name);

    task.taskItem = item;
    item->setParentItem(listContainer);
    tasks.append(task);
}

void TasksPage::sortBy(QString by, bool ascending) {
    for (auto &task : tasks) {
        task.taskItem->setParentItem(nullptr);
    }

    auto get_str = [&by](Task task) { return (task.property(by.toStdString().c_str())).toString().toLower().trimmed(); };

    std::sort(tasks.begin(), tasks.end(),
        [&ascending, &by, &get_str](Task t1, Task t2) { return (get_str(t1) < get_str(t2)) ^ !ascending; });

    for(auto &task : tasks) {
        task.taskItem->setParentItem(listContainer);
    }
}

TasksPage::~TasksPage(){
    for(auto &task : tasks) {
        task.taskItem->deleteLater();
        task.taskItem = nullptr;
    }

    itemComponent->deleteLater();
}
