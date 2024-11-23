#pragma once

#include <cstdio>
#include <future>
#include <thread>
#include <vector>
#include <glib.h>
#include <librdkafka/rdkafka.h>
#include <iostream>
#include <set>
#include <QQuickItem>

#include "common.h"

static volatile sig_atomic_t run = 1;

/**
 * @brief Signal termination of program
 */
static void stop(int sig) { run = 0; }

namespace Kafka {
    class Consumer : public QObject {
        Q_OBJECT
    private:
        static volatile sig_atomic_t run;
        rd_kafka_t *consumer;
        rd_kafka_conf_t *conf;
        rd_kafka_resp_err_t err;
        char errstr[512];
        std::thread listener;
        std::set<const char *> topics;

        int getMessages();
    public:
        //Object part
        Consumer(const char *groupID);
        ~Consumer();

        static Consumer *getInstance(const char *groupID);

        static void stop(int sig);

        template<typename ...Args>
        void addTopics(Args... args) {
            ([&]
            {
                this->topics.insert(args);

                if (this->listener.joinable()) {
                    this->stopListen();
                    this->run = 1;
                    this->startListen();
                }
            } (), ...);
        }

        template<typename ...Args>
        void remove_topics(Args... args) {
            ([&]
            {
                if (topics.find(args) != topics.end()) { 
                    this->topics.erase(args);
                    
                    if (this->listener.joinable()) {
                        this->stopListen();
                        this->run = 1;
                        this->startListen();
                    }
                }
            } (), ...);
        }

        void startListen();
        void stopListen();
    };
}
