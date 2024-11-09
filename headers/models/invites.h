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

        void append(Invite invite);
    private:
        QList<Invite> invites;
    };
}

#endif // INVITES_H
