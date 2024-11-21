#ifndef TASK_FORM_H
#define TASK_FORM_H

#include "base_form.h"
#include "room.h"

class TaskForm : public BaseForm {
    Q_OBJECT
public:
    Room *room;

    TaskForm(QQmlEngine *engine, QQuickItem *parent, Room *room, Models::Task *task);
    ~TaskForm();

public slots:
    void closeTaskForm();

private:
    Models::Task *task;
};

#endif // TASK_FORM_H
