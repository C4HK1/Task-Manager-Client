#include "models/task.h"

u_int64_t Models::Task::ID_counter{};

Models::Task::Task(nlohmann::json task) {
    this->localID = ID_counter;
    ++ID_counter;

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

QString Models::Task::getDeadlineStr() const {
    std::ostringstream oss;
    oss << std::put_time(localtime(&deadline), "%Y-%m-%d %H:%M:%S");
    return oss.str().c_str();
}

Models::DeadlineStatus Models::Task::getDeadlineStatus() const {
    auto left = difftime(deadline, time(0)) / 3600;

    if (left < 0) {
        return DEADLINE_FAILED;
    } else if (left < 1) {
        return DEADLINE_1H_LEFT;
    } else {
        return DEADLINE_OK;
    }
}

QVariant Models::Task::property(const char *name) const{
    int index = staticMetaObject.indexOfProperty(name);
    if(index == -1){
        return QVariant();
    }

    return staticMetaObject.property(index).readOnGadget(this);
}
