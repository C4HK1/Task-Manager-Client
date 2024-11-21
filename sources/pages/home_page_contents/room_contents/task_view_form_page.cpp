#include "task_view_form_page.h"

TaskViewFormPage::TaskViewFormPage(QQmlEngine *engine, TaskForm *form, Room *room, Models::Task *task) :
    BasePage(engine, "qml/MainWorkspaceElements/TaskViewFormPage.qml"),
    room(room), task(task), form(form)
{
    connect(object, SIGNAL(switchToEditPage()), this, SLOT(switchToEditPage()));
}

TaskViewFormPage::~TaskViewFormPage() {

}

void TaskViewFormPage::update() {
    object->setProperty("taskName", task->name);
    object->setProperty("taskDescription", task->description);
}

void TaskViewFormPage::leave() {}

void TaskViewFormPage::switchToEditPage() {
    form->switchToEditMode();
}
