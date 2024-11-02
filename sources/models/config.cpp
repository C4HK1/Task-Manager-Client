#include "models/config.h"

Models::Config::Config(nlohmann::json config) {
    this->avatar = QString::fromStdString(config.at("avatar"));
    this->configuration = QString::fromStdString(config.at("configuration"));
}
