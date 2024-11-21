#ifndef TASK_VIEW_FORM_PAGE_H
#define TASK_VIEW_FORM_PAGE_H

#include "base_page.h"
#include "task_form.h"
#include "room.h"

class TaskViewFormPage : public BasePage {
    Q_OBJECT
public:
    TaskViewFormPage(QQmlEngine *engine, TaskForm *form, Room *room, Models::Task *task);
    ~TaskViewFormPage();

    void update() override;
    void leave() override;

public slots:
    void switchToEditPage();

private:
    TaskForm *form;
    Room *room;
    Models::Task *task;
};

#endif // TASK_VIEW_FORM_PAGE_H
