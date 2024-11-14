#include "models/room.h"

u_int64_t Models::Room::ID_counter{};

Models::Room::Room(nlohmann::json room) {
    this->localID = ID_counter;
    ++ID_counter;

    this->creatorID = room.at("creator ID");
    this->name = QString::fromStdString(room.at("name"));
    this->description = QString::fromStdString(room.at("description"));
    this->creatorName = QString::fromStdString(room.at("creator name"));
}

Models::Room::~Room() {
    // if(roomItem != nullptr)
    //     roomItem->deleteLater();
}

QVariant Models::Room::property(const char *name) const{
    int index = staticMetaObject.indexOfProperty(name);
    if(index == -1){
        return QVariant();
    }

    return staticMetaObject.property(index).readOnGadget(this);
}
