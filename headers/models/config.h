#ifndef MODELS_CONFIG_H
#define MODELS_CONFIG_H

#include <QQuickItem>
#include <nlohmann/json.hpp>

namespace Models {
    struct Config {
        QString avatar, configuration;

        Config() = default;
        Config(nlohmann::json config);
    };
}

#endif // MODELS_CONFIG_H
