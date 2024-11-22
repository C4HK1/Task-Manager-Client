#include <cstdio>
#include <future>
#include <thread>
#include <vector>
#include <glib.h>
#include <librdkafka/rdkafka.h>
#include <iostream>
#include <set>

#include "common.h"

static volatile sig_atomic_t run = 1;

/**
 * @brief Signal termination of program
 */
static void stop(int sig) { run = 0; }

namespace kafka {
    class consumer {
        static volatile sig_atomic_t run;
        rd_kafka_t *consumer_;
        rd_kafka_conf_t *conf;
        rd_kafka_resp_err_t err;
        char errstr[512];
        std::thread listener;
        std::set<const char *> topics;

        int get_messages();
    public:
        //Object part
        consumer(const char *group_ID);
        ~consumer();

        static void stop(int sig);

        template<typename ...Args>
        void add_topics(Args... args) {
            ([&]
            {
                this->topics.insert(args);

                if (this->listener.joinable()) {
                    this->stop_listen();
                    this->run = 1;
                    this->start_listen();
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
                        this->stop_listen();
                        this->run = 1;
                        this->start_listen();
                    }
                }
            } (), ...);
        }

        void start_listen();
        void stop_listen();
    };
}