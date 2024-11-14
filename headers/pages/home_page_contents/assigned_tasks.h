#ifndef ASSIGNED_TASKS_H
#define ASSIGNED_TASKS_H

#include "tasks_list.h"

class HomePage;

class AssignedTasks : public TasksList {
    Q_OBJECT
public:
    AssignedTasks(QQmlEngine *engine, HomePage *homePage);
    ~AssignedTasks() override;
    void update() override;
    void leave() override;
signals:
public slots:
protected:
private:
};

#endif // ASSIGNED_TASKS_H
