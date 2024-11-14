#include "models/invites.h"

Models::Invites::Invites(nlohmann::json invites) {
    for (auto &invite : invites) {
        this->invites.append(Models::Invite(invite));
    }
}

Models::Invite& Models::Invites::operator [](int i) {
    return this->invites[i];
}

void Models::Invites::setType(Models::InviteTypes type) {
    for (auto &invite : this->invites) {
        invite.type = type;
    }
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

void Models::Invites::append(Models::Invites invites) {
    this->invites.append(invites.invites);
}

void Models::Invites::remove(Models::Invite invite) {
    auto senderID = invite.senderID;
    auto receiverID = invite.receiverID;
    auto roomCreatorID = invite.roomCreatorID;
    auto roomName = invite.roomName;

    int i = 0;
    for (auto &invite : invites) {
        if (invite.senderID == senderID &&
            invite.receiverID == receiverID &&
            invite.roomCreatorID == roomCreatorID &&
            invite.roomName == roomName) {
            this->invites.removeAt(i);
        }

        ++i;
    }
}

void Models::Invites::removeAcceptedInvites(Models::Invite invite) {
    auto receiverID = invite.receiverID;
    auto roomCreatorID = invite.roomCreatorID;
    auto roomName = invite.roomName;

    int i = 0;
    for (auto invite : this->invites) {
        if (invite.receiverID == receiverID &&
            invite.roomCreatorID == roomCreatorID &&
            invite.roomName == roomName) {
            this->invites.removeAt(i);
        }
        i += 1;
    }
}

void Models::Invites::clear() {
    this->invites.clear();
}
