#include "models/profile.h"

Models::Profile::Profile(nlohmann::json profile) {
    this->ID = profile.at("ID");
    this->name = QString::fromStdString(profile.at("name"));
    this->login = QString::fromStdString(profile.at("login"));
    this->password = QString::fromStdString(profile.at("password"));
    this->email = QString::fromStdString(profile.at("email"));
    this->phone = QString::fromStdString(profile.at("phone"));
}
