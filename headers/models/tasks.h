#ifndef MODELS_TASKS_H
#define MODELS_TASKS_H

#include <QQuickItem>
#include <nlohmann/json.hpp>

#include "task.h"

namespace Models {
    struct Tasks {
        Tasks() = default;
        Tasks(nlohmann::json tasks);

        Task& operator [](int i);

        QList<Task>::Iterator begin();
        QList<Task>::Iterator end();

        size_t size();

        void append(Task task);
    private:
        QList<Task> tasks;
    };
}

#endif // MODELS_TASKS_H
