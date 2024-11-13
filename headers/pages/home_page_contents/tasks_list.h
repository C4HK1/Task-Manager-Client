#ifndef TASKS_PAGE_H
#define TASKS_PAGE_H

#include "base_element.h"
#include "models.h"

class HomePage;

class TasksList : public BaseElement
{
    Q_OBJECT
public:
    HomePage *homePage;

    TasksList(QQmlEngine *engine, HomePage *homePage);
    virtual ~TasksList();

    void createTaskItem(Models::Task &task);
signals:
public slots:
    void sortBy(QString by, bool ascending = true);
    void tasksInitialization(Models::ServerStatus serverStatus, Models::Tasks tasks);
    void openRoom(int roomCreatorID, QString roomName);
protected:
    QQmlComponent *itemComponent;
    QQuickItem *listContainer;

    Models::Tasks tasks;
private:
};

template <typename T>
concept IsTasksPage = std::is_same<TasksList, T>::value;

#endif // TASKS_PAGE_H
