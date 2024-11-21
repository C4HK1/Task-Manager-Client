#ifndef TASK_CREATION_FORM_H
#define TASK_CREATION_FORM_H

#include "base_form.h"

class Room;

class TaskCreationForm : public BaseForm {
    Q_OBJECT
public:
    Room *room;

    TaskCreationForm(QQmlEngine *engine, QQuickItem *parent, Room *room);
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

    void finishCreateTask(Models::ServerStatus serverStatus, Models::Task task);
protected:
private:
};

#endif // TASK_CREATION_FORM_H
