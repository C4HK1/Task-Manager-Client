#ifndef MODELS_PROFILES_H
#define MODELS_PROFILES_H

#include <QQuickItem>
#include <nlohmann/json.hpp>

#include "profile.h"
#include "task.h"

namespace Models {
    struct Profiles {
        Profiles() = default;
        Profiles(nlohmann::json profiles);

        Profile& operator [](int i);

        QList<Profile>::Iterator begin();
        QList<Profile>::Iterator end();

        size_t size();

        void append(Profile profile);
    private:
        QList<Profile> profiles;
    };
}

#endif // MODELS_PROFILES_H
