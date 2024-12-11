#include "kafka/consumer.h"

Kafka::Consumer::Consumer(const std::string& brokers, const std::string& topicName) : topicName(topicName) {
    this->conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    this->conf->set("metadata.broker.list", brokers, errstr);

    this->consumer = RdKafka::Consumer::create(conf, errstr);
    this->topic = RdKafka::Topic::create(consumer, topicName, nullptr, errstr);

    qInfo() << "topic:" << this->topicName << "subscribed";

    this->listener = std::thread([this](){ this->listen(); });
}

Kafka::Consumer::~Consumer() {
    this->run = 0;
    this->listener.join();

    delete topic;
    delete consumer;
    delete conf;
}

void Kafka::Consumer::startMessageHandling() {
    this->messageHandling = false;
}

void Kafka::Consumer::stopMessageHandling() {
    this->messageHandling = true;
}


void Kafka::Consumer::listen() {
    if(!QDir("data").exists()){
        QDir().mkdir("data");
    }

    QFile file("data/messages.json");
    QByteArray buffer;

    file.open(QIODevice::ReadOnly);
    buffer = file.readAll();
    file.close();

    u_int64_t messagesCount;
    nlohmann::json messages;
    nlohmann::json topic;
    nlohmann::json topics;

    try {
        topics = nlohmann::json::parse(buffer.toStdString());
        topic = topics.at(this->topicName);
        messagesCount = topic.at("messagesCount");
        consumer->start(this->topic, 0, messagesCount);
    } catch(nlohmann::json::exception &exception) {
        messagesCount = 0;
        consumer->start(this->topic, 0, RdKafka::Topic::OFFSET_END - 1);
    }

    while (this->run) {
        if (!this->messageHandling) {
            file.open(QIODevice::ReadOnly);
            buffer = file.readAll();
            file.close();

            try {
                topics = nlohmann::json::parse(buffer.toStdString());
                topic = topics.at(this->topicName);
                messagesCount = topic.at("messagesCount");
                messages = topic.at("messages");

                nlohmann::json message = messages.at("message-" + std::to_string(messagesCount - messages.size()));

                messages.erase("message-" + std::to_string(messagesCount - messages.size()));

                topic.clear();
                topic.push_back(nlohmann::json::object_t::value_type("messagesCount", messagesCount));
                topic.push_back(nlohmann::json::object_t::value_type("messages", messages));

                topics.erase(this->topicName);
                topics.push_back(nlohmann::json::object_t::value_type(this->topicName, topic));

                file.open(QIODevice::WriteOnly);
                file.write(topics.dump().c_str());
                file.close();

                if (message.at("key") == "getting invite") {
                    this->stopMessageHandling();
                    emit this->inviteGetted(message.at("value"));
                }
            } catch(nlohmann::json::exception &exception) {}
        }

        RdKafka::Message* msg = consumer->consume(this->topic, 0, 1000);
        std::string key;
        nlohmann::json value;
        u_int64_t offset;

        if (msg->err() == RdKafka::ERR_NO_ERROR) {
            key = *msg->key();
            value = nlohmann::json::parse(std::string(static_cast<char*>(msg->payload()), msg->len()));
            offset = msg->offset();

            qInfo() << "message getted" << key << value.dump() << offset;

            nlohmann::json topic;
            topic.push_back(nlohmann::json::object_t::value_type("messagesCount", offset + 1));
            nlohmann::json message;
            message.push_back(nlohmann::json::object_t::value_type("key", key));
            message.push_back(nlohmann::json::object_t::value_type("value", value));

            messages.push_back(nlohmann::json::object_t::value_type("message-" + std::to_string(offset), message));
            topic.push_back(nlohmann::json::object_t::value_type("messages", messages));
            topics.push_back(nlohmann::json::object_t::value_type(this->topicName, topic));

            file.open(QIODevice::WriteOnly);
            file.write(topics.dump().c_str());
            file.close();
        } else {
            std::cerr << "Error while consuming: " << msg->errstr() << std::endl;
        }

        delete msg;
    }
}
