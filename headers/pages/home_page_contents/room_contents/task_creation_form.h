#ifndef TASK_CREATION_FORM_H
#define TASK_CREATION_FORM_H

#include "base_element.h"

class Room;

class TaskCreationForm : public BaseElement {
    Q_OBJECT
public:
    Room *room;

    TaskCreationForm(QQmlEngine *engine, QQuickItem *container, Room *roomPage);
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

    void finishCreateTask(Models::ServerStatus serverStatus, Models::Task task);
protected:
private:
};

#endif // TASK_CREATION_FORM_H
