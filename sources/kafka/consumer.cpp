#include <cstdio>
#include <future>
#include <glib.h>
#include <librdkafka/rdkafka.h>
#include <iostream>
#include <thread>
#include <unistd.h>

#include "kafka/consumer.h"
#include "kafka/common.h"

volatile sig_atomic_t Kafka::Consumer::run{1};

/**
 * @brief Signal termination of program
 */

Kafka::Consumer::Consumer(const char *groupID) {
    // Create client configuration
    conf = rd_kafka_conf_new();

    // User-specific properties that you must set
    rd_kafka_conf_res_t res;

    if (rd_kafka_conf_set(conf, "group.id", groupID, errstr, sizeof(errstr)) !=
        RD_KAFKA_CONF_OK) {
        fprintf(stderr, "%s\n", errstr);
        rd_kafka_conf_destroy(conf);
        Kafka::Consumer::run = 0;
        return;
    }

    res = rd_kafka_conf_set(conf, "bootstrap.servers", KAFKA_BROKERS.c_str(), errstr,
                            sizeof(errstr));
    if (res != RD_KAFKA_CONF_OK) {
        g_error("Unable to set config: %s", errstr);
        Kafka::Consumer::run = 0;
        return;
    }
    // Create the Consumer instance.
    consumer = rd_kafka_new(RD_KAFKA_CONSUMER, conf, errstr, sizeof(errstr));
    if (!consumer) {
        g_error("Failed to create new consumer: %s", errstr);
        Kafka::Consumer::run = 0;
        return;
    }
    rd_kafka_poll_set_consumer(consumer);

    // Configuration object is now owned, and freed, by the rd_kafka_t instance.
    conf = NULL;
}

Kafka::Consumer::~Consumer() {
    this->stopListen();

    // Close the consumer: commit final offsets and leave the group.
    g_message("Closing consumer");
    rd_kafka_consumer_close(consumer);

    // Destroy the consumer.
    rd_kafka_destroy(consumer);
}

Kafka::Consumer *Kafka::Consumer::getInstance(const char *groupID) {
    static Kafka::Consumer consumer(groupID);
    return &consumer;
}

void Kafka::Consumer::stop(int sig) { Kafka::Consumer::run = 0; }

int Kafka::Consumer::getMessages() {
    // Install a signal handler for clean shutdown.
    signal(SIGINT, stop);

    while (Kafka::Consumer::run) {
        // Convert the list of topics to a format suitable for librdkafka.
        rd_kafka_topic_partition_list_t *subscription =
            rd_kafka_topic_partition_list_new(1);

        for (auto topic : this->topics) {
            rd_kafka_topic_partition_list_add(subscription, topic, RD_KAFKA_PARTITION_UA);
        }

        // Subscribe to the list of topics.
        err = rd_kafka_subscribe(consumer, subscription);

        if (err) {
            printf("Subscription to: %d topics failed\n", subscription->cnt);
            rd_kafka_topic_partition_list_destroy(subscription);
            continue;
        }

        rd_kafka_topic_partition_list_destroy(subscription);

        // Start polling for messages.
        while (run) {
            rd_kafka_message_t *consumerMessage;

            consumerMessage = rd_kafka_consumer_poll(consumer, 500);
            if (!consumerMessage) {
                g_message(("Waiting for..."));
                continue;
            }

            if (consumerMessage->err) {
                if (consumerMessage->err == RD_KAFKA_RESP_ERR__PARTITION_EOF) {
                    /* We can ignore this error - it just means we've read
                    * everything and are waiting for more data.
                    */
                } else {
                    g_message("Consumer error: %s",
                                rd_kafka_message_errstr(consumerMessage));
                    break;
                }
            } else {
                g_message("Consumed event from topic %s: key = %.*s value = %s",
                        rd_kafka_topic_name(consumerMessage->rkt),
                        (int)consumerMessage->key_len, (char *)consumerMessage->key,
                        (char *)consumerMessage->payload);
            }

            // Free the message when we're done.
            rd_kafka_message_destroy(consumerMessage);
        }
    }

    return 0;
}

void Kafka::Consumer::startListen() {
    if (this->listener.joinable()) {
        std::cout << "Listener is alredy started\n";
    } else {
        std::cout << "Start listening\n";
        
        this->listener = std::thread([this](){this->getMessages();});
    }
}

void Kafka::Consumer::stopListen() {
    Kafka::Consumer::run = 0;

    std::cout << "Stop listening\n";

    if (this->listener.joinable()) 
        this->listener.join();
}
