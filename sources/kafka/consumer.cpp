#include <cstdio>
#include <future>
#include <glib.h>
#include <librdkafka/rdkafka.h>
#include <iostream>
#include <thread>
#include <unistd.h>

#include "kafka/consumer.h"
#include "kafka/common.h"

volatile sig_atomic_t kafka::consumer::run{1};

/**
 * @brief Signal termination of program
 */

kafka::consumer::consumer(const char *group_ID) {
    // Create client configuration
    conf = rd_kafka_conf_new();

    // User-specific properties that you must set
    rd_kafka_conf_res_t res;

    if (rd_kafka_conf_set(conf, "group.id", group_ID, errstr, sizeof(errstr)) !=
        RD_KAFKA_CONF_OK) {
        fprintf(stderr, "%s\n", errstr);
        rd_kafka_conf_destroy(conf);
        return;
    }

    res = rd_kafka_conf_set(conf, "bootstrap.servers", KAFKA_BROKERS, errstr,
                            sizeof(errstr));
    if (res != RD_KAFKA_CONF_OK) {
        g_error("Unable to set config: %s", errstr);
        exit(1);
    }
    // Create the Consumer instance.
    consumer_ = rd_kafka_new(RD_KAFKA_CONSUMER, conf, errstr, sizeof(errstr));
    if (!consumer_) {
        g_error("Failed to create new consumer: %s", errstr);
        return;
    }
    rd_kafka_poll_set_consumer(consumer_);

    // Configuration object is now owned, and freed, by the rd_kafka_t instance.
    conf = NULL;
}

kafka::consumer::~consumer() {
    this->stop_listen();

    // Close the consumer: commit final offsets and leave the group.
    g_message("Closing consumer");
    rd_kafka_consumer_close(consumer_);

    // Destroy the consumer.
    rd_kafka_destroy(consumer_);
}

void kafka::consumer::stop(int sig) { run = 0; }

int kafka::consumer::get_messages() {
    // Install a signal handler for clean shutdown.
    signal(SIGINT, stop);

        // Convert the list of topics to a format suitable for librdkafka.
    rd_kafka_topic_partition_list_t *subscription =
        rd_kafka_topic_partition_list_new(1);

    for (auto topic : this->topics) {
        rd_kafka_topic_partition_list_add(subscription, topic, RD_KAFKA_PARTITION_UA);
    }

    // Subscribe to the list of topics.
    err = rd_kafka_subscribe(consumer_, subscription);

    if (err) {
        printf("Subscription to: %d topics failed\n", subscription->cnt);
        rd_kafka_topic_partition_list_destroy(subscription);
        return 1;
    }

    rd_kafka_topic_partition_list_destroy(subscription);

    // Start polling for messages.
    while (run) {
        rd_kafka_message_t *consumer_message;

        consumer_message = rd_kafka_consumer_poll(consumer_, 500);
        if (!consumer_message) {
            g_message(("Waiting for..."));
            continue;
        }

        if (consumer_message->err) {
            if (consumer_message->err == RD_KAFKA_RESP_ERR__PARTITION_EOF) {
                /* We can ignore this error - it just means we've read
                * everything and are waiting for more data.
                */
            } else {
                g_message("Consumer error: %s",
                            rd_kafka_message_errstr(consumer_message));
                return 1;
            }
        } else {
            g_message("Consumed event from topic %s: key = %.*s value = %s",
                    rd_kafka_topic_name(consumer_message->rkt),
                    (int)consumer_message->key_len, (char *)consumer_message->key,
                    (char *)consumer_message->payload);
        }

        // Free the message when we're done.
        rd_kafka_message_destroy(consumer_message);
    }

    return 0;
}

void kafka::consumer::start_listen() {
    if (this->listener.joinable()) {
        std::cout << "Listener is alredy started\n";
    } else {
        std::cout << "Start listening\n";
        
        this->listener = std::thread([this](){this->get_messages();});
    }
}

void kafka::consumer::stop_listen() {
    kafka::consumer::run = 0;

    std::cout << "Stop listening\n";

    if (this->listener.joinable()) 
        this->listener.join();
}
