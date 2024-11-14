#ifndef REVIEWED_TASKS_H
#define REVIEWED_TASKS_H

#include "tasks_list.h"

class HomePage;

class ReviewedTasks : public TasksList {
    Q_OBJECT
public:
    ReviewedTasks(QQmlEngine *engine, HomePage *homePage);
    ~ReviewedTasks() override;
    void update() override;
    void leave() override;
signals:
public slots:
protected:
private:
};

#endif // REVIEWED_TASKS_H
