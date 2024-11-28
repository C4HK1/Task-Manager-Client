#ifndef TASK_FORM_H
#define TASK_FORM_H

#include "base_form.h"
#include "room.h"
#include "navigation_service.h"
#include "network_manager.h"

class TaskForm : public BaseForm {
    Q_OBJECT
public:
    Room *room;

    TaskForm(QQmlEngine *engine, QQuickItem *parent, Room *room, Models::Task *task);
    ~TaskForm();

public slots:
    void closeTaskForm();
    void switchToEditMode();
    void switchToViewMode();

    void setTaskAssignees(Models::ServerStatus status, Models::Profiles profiles);
    void setTaskReviewers(Models::ServerStatus status, Models::Profiles profiles);

private:
    NavigationService *nav_service;
    NetworkManager *net_manager;
    Models::Task *task;
    Models::Profiles assignees;
    Models::Profiles reviewers;
};

#endif // TASK_FORM_H
