#include "task_form.h"
#include "task_edit_form_page.h"
#include "task_view_form_page.h"

TaskForm::TaskForm(QQmlEngine *engine, QQuickItem *parent, Room *room, Models::Task *task) :
    BaseForm(engine, parent, "qml/DefaultElements/DefaultForm.qml"),
    room(room), task(task),
    nav_service(new NavigationService(object))
{
    switchToViewMode();
}

TaskForm::~TaskForm() {
    nav_service->deleteLater();
}

void TaskForm::closeTaskForm() {
    this->room->closeForm();
}

void TaskForm::switchToViewMode() {
    nav_service->switchTo(new TaskViewFormPage(engine, this, room, task));
}

void TaskForm::switchToEditMode() {
    nav_service->switchTo(new TaskEditFormPage(engine, this, room, task));
}
