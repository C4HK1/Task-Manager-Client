#include "tasks_page.h"

TasksPage::TasksPage(QQmlEngine *engine, QQuickItem *container) :
    BasePage(engine, container, "qml/Tasks.qml"),
    item_component(new QQmlComponent(engine, QUrl::fromLocalFile("qml/MainWorkspaceElements/TaskListItem.qml"))),
    list_container(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("list_container"))
{
    connect(object, SIGNAL(sortBy(QString,bool)), this, SLOT(sortBy(QString,bool)));
}

void TasksPage::createTaskItem(TaskInfo *ti){
    auto item = qobject_cast<QQuickItem*>(item_component->create(engine->rootContext()));
    item->findChild<QQuickItem*>("task_name")->setProperty("text", ti->task_name);
    item->findChild<QQuickItem*>("room_name")->setProperty("text", ti->parent->room_name);
    item->setProperty("room_id", ti->room_id);

    ti->task_item = item;
    item->setParentItem(list_container);
    tasks_infos.append(ti);
}

void TasksPage::sortBy(QString by, bool ascending) {
    for (auto &ti : tasks_infos) {
        ti->task_item->setParentItem(nullptr);
    }

    auto get_str = [&by](TaskInfo *ti) { return (ti->property(by.toStdString().c_str())).toString().toLower().trimmed(); };

    std::sort(tasks_infos.begin(), tasks_infos.end(),
        [&ascending, &by, &get_str](TaskInfo *t1, TaskInfo *t2) { return (get_str(t1) < get_str(t2)) ^ !ascending; });

    for(auto &ti : tasks_infos) {
        ti->task_item->setParentItem(list_container);
    }
}

TasksPage::~TasksPage(){
    for(auto &ti : tasks_infos) {
        ti->task_item->deleteLater();
        ti->task_item = nullptr;
    }

    item_component->deleteLater();
}
