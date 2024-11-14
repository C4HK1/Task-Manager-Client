#ifndef MODELS_ROOM_H
#define MODELS_ROOM_H

#include <QQuickItem>
#include <nlohmann/json.hpp>

namespace Models {
    struct Room {
        Q_GADGET
    public:
        u_int64_t localID;
        u_int64_t creatorID;
        QString name, description, creatorName;

        Room() = default;
        Room(nlohmann::json room);
        ~Room();

        QVariant property(const char *name) const;
    private:
        static u_int64_t ID_counter;
    };
}

#endif // MODELS_ROOM_H
