#ifndef INVITE_H
#define INVITE_H

#include <QQuickItem>
#include <nlohmann/json.hpp>

namespace Models {
    enum InviteTypes : u_int64_t {
        RECEIVED,
        SENDED
    };

    struct Invite {
        Q_GADGET
        Q_PROPERTY(QString senderName READ getSenderName)
        Q_PROPERTY(QString roomName READ getRoomName)

    public:
        u_int64_t localID;
        u_int64_t senderID = 0;
        u_int64_t receiverID = 0;
        u_int64_t roomCreatorID = 0;
        QString roomName, senderName, receiverName;

        InviteTypes type;

        bool operator ==(Invite invite);

        QString getSenderName() const { return this->senderName; }
        QString getRoomName() const { return this->roomName; }

        Invite() = default;

        Invite(nlohmann::json task);

        // ~Task() { if(taskItem != nullptr) taskItem->deleteLater(); }

        QVariant property(const char *name) const;
    private:
        static u_int64_t ID_counter;
    };
}

#endif // INVITE_H
