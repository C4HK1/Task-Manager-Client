#pragma once

#include <glib.h>
#include <librdkafka/rdkafka.h>
#include <cstring>
#include <string>
#include <QQuickItem>

namespace Kafka {
    constexpr std::string KAFKA_BROKERS{"localhost"};

    class Common : public QObject {
        Q_OBJECT
    public:
        static void setConfig(rd_kafka_conf_t *conf,
                               char *key, 
                               char *value);
        static void drMsgCb(rd_kafka_t *kafka_handle,
                              const rd_kafka_message_t *rkmessage,
                              void *opaque);
    };
}
