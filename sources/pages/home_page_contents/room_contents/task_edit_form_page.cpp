#include "task_edit_form_page.h"

TaskEditFormPage::TaskEditFormPage(QQmlEngine *engine, TaskForm *form, Room *room, Models::Task *task) :
    BasePage(engine, "qml/MainWorkspaceElements/TaskEditFormPage.qml"),
    room(room), task(task), form(form)
{
    connect(object, SIGNAL(switchToViewPage()), this, SLOT(switchToViewPage()));
}

TaskEditFormPage::~TaskEditFormPage() {

}

void TaskEditFormPage::update() {
    object->setProperty("taskName", task->name);
    object->setProperty("taskDescription", task->description);
}

void TaskEditFormPage::leave() {
    task->name = object->property("taskName").toString();
    task->description = object->property("taskDescription").toString();
    form->room->updateItem(task);
}

void TaskEditFormPage::switchToViewPage() {
    form->switchToViewMode();
}
