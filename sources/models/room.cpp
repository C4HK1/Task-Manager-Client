#include "models/room.h"

Models::Room::Room(nlohmann::json room) {
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
