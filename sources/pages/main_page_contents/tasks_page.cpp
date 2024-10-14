#include "tasks_page.h"

TasksPage::TasksPage(QQmlEngine *engine, QQuickItem *container) :
    BasePage(engine, container, "qml/Tasks.qml"),
    item_component(new QQmlComponent(engine, QUrl::fromLocalFile("qml/MainWorkspaceElements/TaskListItem.qml"))),
    list_container(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("list_container"))
{}

void TasksPage::createTaskItem(TaskInfo *ti){
    auto item = qobject_cast<QQuickItem*>(item_component->create(engine->rootContext()));
    item->findChild<QQuickItem*>("task_name")->setProperty("text", ti->task_name);
    item->findChild<QQuickItem*>("room_name")->setProperty("text", ti->parent->room_name);
    item->setProperty("room_id", ti->room_id);

    ti->task_item = item;
    item->setParentItem(list_container);
    tasks_items.append(item);
}

void TasksPage::sortBy(bool ascending) {
    for (auto &ti : tasks_items) {
        ti->setParentItem(nullptr);
    }

    std::sort(tasks_items.begin(), tasks_items.end(),
              [&ascending](QQuickItem *t1, QQuickItem *t2) {
        return (t1->findChild<QQuickItem*>("task_name")->property("text").toString() < t2->findChild<QQuickItem*>("task_name")->property("text").toString()) ^ !ascending;
    });

    for(auto &ti : tasks_items) {
        ti->setParentItem(list_container);
    }
}

TasksPage::~TasksPage(){
    for(auto &item : tasks_items) {
        item->deleteLater();
    }

    item_component->deleteLater();
}
