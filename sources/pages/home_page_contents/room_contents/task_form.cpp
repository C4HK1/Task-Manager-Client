#include "task_form.h"

TaskForm::TaskForm(QQmlEngine *engine, QQuickItem *parent, Room *room, Models::Task *task) :
    BaseForm(engine, parent, "qml/MainWorkspaceElements/TaskForm.qml"),
    room(room), task(task)
{
    object->setProperty("taskName", task->name);
    object->setProperty("taskDescription", task->description);
}

TaskForm::~TaskForm() {

}

void TaskForm::closeTaskForm() {
    this->room->closeForm();
}
