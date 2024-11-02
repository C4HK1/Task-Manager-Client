#ifndef MODELS_PROFILE_H
#define MODELS_PROFILE_H

#include <QQuickItem>
#include <nlohmann/json.hpp>

namespace Models {
    struct Profile {
        Q_GADGET
    public:
        u_int64_t ID;
        QString name, login, password, email, phone;

        Profile() = default;

        Profile(nlohmann::json profile);
    };
}

#endif // MODELS_PROFILE_H
