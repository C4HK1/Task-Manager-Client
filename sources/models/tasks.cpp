#include "models/tasks.h"

Models::Tasks::Tasks(nlohmann::json tasks) {
    for (auto &task : tasks) {
        this->tasks.append(Models::Task(task));
    }
}

Models::Task& Models::Tasks::operator [](int i) {
    return this->tasks[i];
}

QList<Models::Task>::Iterator Models::Tasks::begin() {
    return this->tasks.begin();
}

QList<Models::Task>::Iterator Models::Tasks::end() {
    return this->tasks.end();
}

size_t Models::Tasks::size() {
    return this->tasks.size();
}

void Models::Tasks::append(Models::Task task) {
    this->tasks.append(task);
}
