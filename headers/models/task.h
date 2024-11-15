#ifndef MODELS_TASK_H
#define MODELS_TASK_H

#include <QQuickItem>
#include <nlohmann/json.hpp>

#include "room.h"

namespace Models {
    struct Task {
        Q_GADGET
        Q_PROPERTY(u_int64_t roomCreatorID READ getRoomCreatorID)
        Q_PROPERTY(QString roomName READ getRoomName)
        Q_PROPERTY(QString taskName MEMBER name)
        Q_PROPERTY(QString creatorName MEMBER creatorName)
        Q_PROPERTY(QString label MEMBER label)
        Q_PROPERTY(QString deadline READ getDeadlineStr)

    public:
        u_int64_t localID;
        u_int64_t creatorID, status;
        QString name, creatorName, description, label;
        std::time_t creationTime, deadline;

        Room parent;

        QString getRoomName() const { return parent.name; }
        u_int64_t getRoomCreatorID() const { return parent.creatorID; }
        QString getDeadlineStr() const;

        Task() = default;

        Task(nlohmann::json task);

        // ~Task() { if(taskItem != nullptr) taskItem->deleteLater(); }

        QVariant property(const char *name) const;
    private:
        static u_int64_t ID_counter;
    };
}

#endif // MODELS_TASK_H
