#ifndef TASKS_PAGE_H
#define TASKS_PAGE_H

#include "base_page.h"
#include "content_structures.h"

class MainPage;

class TasksPage : public BasePage
{
    Q_OBJECT
public:
    TasksPage(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage);
    ~TasksPage();

    void createTaskItem(Task &task);

public slots:
    void sortBy(QString by, bool ascending = true);
    void tasksInitialization(ServerStatus serverStatus, Tasks tasks);
    void openRoom(int roomCreatorID, QString roomName);

protected:
    Tasks tasks;
    MainPage *mainPage;
    QQmlComponent *itemComponent;
    QQuickItem *listContainer;
};

template <typename T>
concept IsTasksPage = std::is_same<TasksPage, T>::value;

#endif // TASKS_PAGE_H
