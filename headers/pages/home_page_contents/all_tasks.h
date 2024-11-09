#ifndef ALL_TASKS_H
#define ALL_TASKS_H

#include "tasks_list.h"

class HomePage;

class AllTasks : public TasksList {
    Q_OBJECT
public:
    AllTasks(QQmlEngine *engine, QQuickItem *container, HomePage *homePage);
    ~AllTasks() override;
signals:
public slots:
protected:
private:
};

#endif // ALL_TASKS_H
