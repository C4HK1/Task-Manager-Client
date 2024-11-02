#include "models/profiles.h"

Models::Profiles::Profiles(nlohmann::json profiles) {
    for (auto profile : profiles) {
        this->profiles.append(profile);
    }
}

Models::Profile& Models::Profiles::operator [](int i) {
    return this->profiles[i];
}

QList<Models::Profile>::Iterator Models::Profiles::begin() {
    return this->profiles.begin();
}

QList<Models::Profile>::Iterator Models::Profiles::end() {
    return this->profiles.end();
}

size_t Models::Profiles::size() {
    return this->profiles.size();
}

void Models::Profiles::append(Models::Profile profile) {
    this->profiles.append(profile);
}
