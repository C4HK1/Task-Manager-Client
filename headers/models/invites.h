#ifndef INVITES_H
#define INVITES_H

#include <QQuickItem>
#include <nlohmann/json.hpp>
#include "models/invite.h"

namespace Models {
    struct Invites {
        Invites() = default;
        Invites(nlohmann::json invites);

        Invite& operator [](int i);

        QList<Invite>::Iterator begin();
        QList<Invite>::Iterator end();

        size_t size();

        void setType(Models::InviteTypes type);

        void append(Invite invite);
        void append(Invites invites);
        void remove(Invite invite);
        void removeAcceptedInvites(Models::Invite invite);
    private:
        QList<Invite> invites;
    };
}

#endif // INVITES_H
