#ifndef TASK_CREATION_PAGE_H
#define TASK_CREATION_PAGE_H

#include "base_page.h"
#include "room_page.h"

class MainPage;

class TaskCreationPage : public BasePage {
    Q_OBJECT
public:
    TaskCreationPage(QQmlEngine *engine, QQuickItem *container);
    ~TaskCreationPage();
signals:
    void closeTaskCreatiornForm();
public slots:
    void createTask(int roomCreatorID,
                    QString roomName,
                    QString taskName,
                    QString description,
                    QString label,
                    int status,
                    int timeToLive);
    void finishCreateTask(ServerStatus serverStatus, Task task);

private:
};

#endif // TASK_CREATION_PAGE_H
