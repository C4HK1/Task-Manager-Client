#include "models/rooms.h"

Models::Rooms::Rooms(nlohmann::json rooms) {
    for (auto room : rooms) {
        this->rooms.append(room);
    }
}

Models::Room& Models::Rooms::operator [](int i) {
    return this->rooms[i];
}

QList<Models::Room>::Iterator Models::Rooms::begin() {
    return this->rooms.begin();
}

QList<Models::Room>::Iterator Models::Rooms::end() {
    return this->rooms.end();
}

size_t Models::Rooms::size() {
    return this->rooms.size();
}

void Models::Rooms::append(Models::Room room) {
    this->rooms.append(room);
}
