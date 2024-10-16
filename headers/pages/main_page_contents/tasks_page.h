#ifndef TASKS_PAGE_H
#define TASKS_PAGE_H

#include <QQmlContext>
#include "base_page.h"
#include "content_structures.h"

class TasksPage : public BasePage
{
    Q_OBJECT
public:
    TasksPage(QQmlEngine *engine, QQuickItem *container);
    void createTaskItem(TaskInfo *ti);
    void sortBy(bool ascending = true);
    ~TasksPage();

signals:
    void addTask(TaskInfo ti);

protected:
    QList<QQuickItem*> tasks_items;
    QQmlComponent *item_component;
    QQuickItem *list_container;
};

template <typename T>
concept IsTasksPage = std::is_same<TasksPage, T>::value;

#endif // TASKS_PAGE_H
