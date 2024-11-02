#include "models/task.h"

Models::Task::Task(nlohmann::json task) {
    this->parent.creatorID = task.at("room creator ID");
    this->parent.name = QString::fromStdString(task.at("room name"));
    this->creatorID = task.at("creator ID");
    this->name = QString::fromStdString(task.at("name"));
    this->description = QString::fromStdString(task.at("description"));
    this->label = QString::fromStdString(task.at("label"));
    this->status = task.at("status");
    this->creationTime = task.at("creation time");
    this->deadline = task.at("deadline");
    this->creatorName = QString::fromStdString(task.at("creator name"));
}

// Models::Task::~Task() { if(taskItem != nullptr) taskItem->deleteLater(); }

QVariant Models::Task::property(const char *name) const{
    int index = staticMetaObject.indexOfProperty(name);
    if(index == -1){
        return QVariant();
    }

    return staticMetaObject.property(index).readOnGadget(this);
}
