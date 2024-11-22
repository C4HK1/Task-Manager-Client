#include <glib.h>
#include <librdkafka/rdkafka.h>

#include "kafka/common.h"

/* Wrapper to set config values and error out if needed.
 */
void Kafka::Common::setConfig(rd_kafka_conf_t *conf, char *key, char *value) {
    char errstr[512];
    rd_kafka_conf_res_t res;

    res = rd_kafka_conf_set(conf, key, value, errstr, sizeof(errstr));
    if (res != RD_KAFKA_CONF_OK) {
        g_error("Unable to set config: %s", errstr);
        exit(1);
    }
}

void Kafka::Common::drMsgCb(rd_kafka_t *kafkaHandle,
                       const rd_kafka_message_t *rkmessage,
                       void *opaque) {
    if (rkmessage->err) {
        g_error("Message delivery failed: %s", rd_kafka_err2str(rkmessage->err));
    }
}
