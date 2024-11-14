#include "models/invite.h"

u_int64_t Models::Invite::ID_counter{};

Models::Invite::Invite(nlohmann::json invite) {
    this->localID = ID_counter;
    ++ID_counter;

    this->senderID = invite.at("sender ID");
    this->receiverID = invite.at("receiver ID");
    this->roomCreatorID = invite.at("room creator ID");
    this->roomName = QString::fromStdString(invite.at("room name"));
    this->senderName = QString::fromStdString(invite.at("sender name"));
    this->receiverName = QString::fromStdString(invite.at("receiver name"));
}

bool Models::Invite::operator ==(Models::Invite invite) {
    return this->senderID == invite.senderID &&
           this->receiverID == invite.receiverID &&
           this->roomCreatorID == invite.roomCreatorID &&
           this->roomName == invite.roomName;
}

QVariant Models::Invite::property(const char *name) const{
    int index = staticMetaObject.indexOfProperty(name);
    if(index == -1){
        return QVariant();
    }

    return staticMetaObject.property(index).readOnGadget(this);
}
