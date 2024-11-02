#ifndef TASK_CREATION_FORM_H
#define TASK_CREATION_FORM_H

#include "base_page.h"

class RoomPage;

class TaskCreationForm : public BasePage {
    Q_OBJECT
public:
    RoomPage *roomPage;

    TaskCreationForm(QQmlEngine *engine, QQuickItem *container, RoomPage *roomPage);
    ~TaskCreationForm();
signals:
public slots:
    void createTask(int roomCreatorID,
                    QString roomName,
                    QString taskName,
                    QString description,
                    QString label,
                    int status,
                    int timeToLive);
    void closeTaskCreationForm();

    void finishCreateTask(ServerStatus serverStatus, Task task);

private:
};

#endif // TASK_CREATION_FORM_H
