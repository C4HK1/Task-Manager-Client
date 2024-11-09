#ifndef REVIEWED_TASKS_H
#define REVIEWED_TASKS_H

#include "tasks_list.h"

class HomePage;

class ReviewedTasks : public TasksList {
    Q_OBJECT
public:
    ReviewedTasks(QQmlEngine *engine, QQuickItem *container, HomePage *homePage);
    ~ReviewedTasks() override;
signals:
public slots:
protected:
private:
};

#endif // REVIEWED_TASKS_H
