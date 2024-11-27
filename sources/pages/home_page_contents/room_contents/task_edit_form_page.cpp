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

    std::tm local_tm = *localtime(&task->deadline);
    object->setProperty("year", local_tm.tm_year + 1900);
    object->setProperty("month", local_tm.tm_mon + 1);
    object->setProperty("day", local_tm.tm_mday);
    object->setProperty("hour", local_tm.tm_hour);
    object->setProperty("minute", local_tm.tm_min);
}

void TaskEditFormPage::leave() {
    task->name = object->property("taskName").toString();
    task->description = object->property("taskDescription").toString();

    std::tm local_tm{};
    local_tm.tm_year = object->property("year").toInt() - 1900;
    local_tm.tm_mon = object->property("month").toInt() - 1;
    local_tm.tm_mday = object->property("day").toInt();
    local_tm.tm_hour = object->property("hour").toInt();
    local_tm.tm_min = object->property("minute").toInt();
    task->deadline = mktime(&local_tm);

    form->room->updateItem(task);
}

void TaskEditFormPage::switchToViewPage() {
    form->switchToViewMode();
}
