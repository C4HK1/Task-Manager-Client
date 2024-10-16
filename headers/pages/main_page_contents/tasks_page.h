#ifndef TASKS_PAGE_H
#define TASKS_PAGE_H

#include "base_page.h"
#include "content_structures.h"

class TasksPage : public BasePage
{
    Q_OBJECT
public:
    TasksPage(QQmlEngine *engine, QQuickItem *container);
    void createTaskItem(TaskInfo *ti);
    ~TasksPage();

public slots:
    void sortBy(QString by, bool ascending = true);

protected:
    QList<TaskInfo*> tasks_infos;
    QQmlComponent *item_component;
    QQuickItem *list_container;
};

template <typename T>
concept IsTasksPage = std::is_same<TasksPage, T>::value;

#endif // TASKS_PAGE_H
