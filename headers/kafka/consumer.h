#pragma once

#include <QQuickItem>
#include <nlohmann/json.hpp>
#include <librdkafka/rdkafkacpp.h>
#include <iostream>
#include <string>
#include <librdkafka/rdkafkacpp.h>
#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <QFile>
#include <QDir>
#include <librdkafka/rdkafkacpp.h>
#include <thread>

namespace Kafka {
    class Consumer : public QObject {
        Q_OBJECT
    public:
        Consumer(const std::string& brokers, const std::string& topicName);
        ~Consumer();

        void stopMessageHandling();

        void startMessageHandling();

        void listen();

    private:
        RdKafka::Conf* conf;
        RdKafka::Consumer* consumer;
        RdKafka::Topic* topic;
        std::string errstr;
        std::thread listener;
        bool messageHandling = false;
        int run = 1;
        std::string topicName;
    signals:
        void inviteGetted(nlohmann::json message);
    };
}
