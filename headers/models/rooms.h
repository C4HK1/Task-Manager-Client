#ifndef MODELS_ROOMS_H
#define MODELS_ROOMS_H

#include <QQuickItem>
#include <nlohmann/json.hpp>

#include "room.h"

namespace Models {
    struct Rooms {
        Rooms() = default;
        Rooms(nlohmann::json rooms);

        Room& operator [](int i);

        QList<Room>::Iterator begin();
        QList<Room>::Iterator end();

        size_t size();

        void append(Room room);
    private:
        QList<Room> rooms;
    };
}

#endif // MODELS_ROOMS_H
