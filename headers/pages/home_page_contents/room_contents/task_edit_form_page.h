#ifndef TASK_EDIT_FORM_PAGE_H
#define TASK_EDIT_FORM_PAGE_H

#include "base_page.h"
#include "task_form.h"
#include "room.h"

class TaskEditFormPage : public BasePage {
    Q_OBJECT
public:
    TaskEditFormPage(QQmlEngine *engine, TaskForm *form, Room *room, Models::Task *task);
    ~TaskEditFormPage();

    void update() override;
    void leave() override;

public slots:
    void switchToViewPage();

private:
    TaskForm *form;
    Room *room;
    Models::Task *task;
};

#endif // TASK_EDIT_FORM_PAGE_H
