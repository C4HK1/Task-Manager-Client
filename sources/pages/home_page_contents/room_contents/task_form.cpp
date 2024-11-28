#include "task_form.h"
#include "task_edit_form_page.h"
#include "task_view_form_page.h"

TaskForm::TaskForm(QQmlEngine *engine, QQuickItem *parent, Room *room, Models::Task *task) :
    BaseForm(engine, parent, "qml/DefaultElements/DefaultForm.qml"),
    room(room), task(task),
    nav_service(new NavigationService(object)),
    net_manager(NetworkManager::getInstance())
{
    connect(net_manager, &NetworkManager::finishGetTaskAssigneesResponseHandling, this, &TaskForm::setTaskAssignees);
    connect(net_manager, &NetworkManager::finishGetTaskReviewersResponseHandling, this, &TaskForm::setTaskReviewers);
    net_manager->sendGetTaskAssignees(task->getRoomCreatorID(), task->getRoomName(), task->name);
    net_manager->sendGetTaskReviewers(task->getRoomCreatorID(), task->getRoomName(), task->name);

    switchToViewMode();
}

TaskForm::~TaskForm() {
    nav_service->deleteLater();
}

void TaskForm::closeTaskForm() {
    this->room->closeForm();
}

void TaskForm::setTaskAssignees(Models::ServerStatus status, Models::Profiles profiles) {
    this->assignees = profiles;
}

void TaskForm::setTaskReviewers(Models::ServerStatus status, Models::Profiles profiles) {
    this->reviewers = profiles;
}

void TaskForm::switchToViewMode() {
    nav_service->switchTo(new TaskViewFormPage(engine, this, room, task));
}

void TaskForm::switchToEditMode() {
    nav_service->switchTo(new TaskEditFormPage(engine, this, room, task));
}
