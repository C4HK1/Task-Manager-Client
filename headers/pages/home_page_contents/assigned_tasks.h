#ifndef ASSIGNED_TASKS_H
#define ASSIGNED_TASKS_H

#include "tasks_list.h"

class HomePage;

class AssignedTasks : public TasksList {
    Q_OBJECT
public:
    AssignedTasks(QQmlEngine *engine, QQuickItem *container, HomePage *homePage);
    ~AssignedTasks() override;
signals:
public slots:
protected:
private:
};

#endif // ASSIGNED_TASKS_H
