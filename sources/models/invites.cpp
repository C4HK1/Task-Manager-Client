#include "models/invites.h"

Models::Invites::Invites(nlohmann::json invites) {
    for (auto &invite : invites) {
        this->invites.append(Models::Invite(invite));
    }
}

Models::Invite& Models::Invites::operator [](int i) {
    return this->invites[i];
}

QList<Models::Invite>::Iterator Models::Invites::begin() {
    return this->invites.begin();
}

QList<Models::Invite>::Iterator Models::Invites::end() {
    return this->invites.end();
}

size_t Models::Invites::size() {
    return this->invites.size();
}

void Models::Invites::append(Models::Invite invite) {
    this->invites.append(invite);
}
