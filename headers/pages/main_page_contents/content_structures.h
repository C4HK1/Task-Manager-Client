#ifndef CONTENT_STRUCTURES_H
#define CONTENT_STRUCTURES_H

#include <QQuickItem>
#include <chrono>
#include <nlohmann/json.hpp>

struct Task;

struct Profile {
    Q_GADGET
public:
    u_int64_t ID;
    QString name, login, password, email, phone;

    Profile() = default;

    Profile(nlohmann::json profile) {
        this->ID = profile.at("ID");
        this->name = QString::fromStdString(profile.at("name"));
        this->login = QString::fromStdString(profile.at("login"));
        this->password = QString::fromStdString(profile.at("password"));
        this->email = QString::fromStdString(profile.at("email"));
        this->phone = QString::fromStdString(profile.at("phone"));
    }
};

struct Profiles {
    friend std::vector<Task>;

    Profiles() = default;
    Profiles(nlohmann::json profiles) {
        for (auto profile : profiles) {
            this->profiles.append(profile);
        }
    }

    Profile& operator [](int i) {
        return this->profiles[i];
    }

    size_t size() {
        return this->profiles.size();
    }
private:
    QList<Profile> profiles;
};

struct Room {
    Q_GADGET
public:
    u_int64_t creatorID;
    QString name, description, creatorName;

    QQuickItem *roomItem = nullptr;

    Room() {};

    Room(nlohmann::json room) {
        this->creatorID = room.at("creator ID");
        this->name = QString::fromStdString(room.at("name"));
        this->description = QString::fromStdString(room.at("description"));
        this->creatorName = QString::fromStdString(room.at("creator name"));
    }

    ~Room() { if(roomItem != nullptr) roomItem->deleteLater(); }

    QVariant property(const char *name) const{
        int index = staticMetaObject.indexOfProperty(name);
        if(index == -1){
            return QVariant();
        }

        return staticMetaObject.property(index).readOnGadget(this);
    }
};

struct Rooms {
    Rooms() {};
    Rooms(nlohmann::json rooms) {
        for (auto room : rooms) {
            this->rooms.append(room);
        }
    }

    Room& operator [](int i) {
        return this->rooms[i];
    }

    auto begin() {
        return this->rooms.begin();
    }

    auto end() {
        return this->rooms.end();
    }

    size_t size() {
        return this->rooms.size();
    }
private:
    QList<Room> rooms;
};

struct Task {
    Q_GADGET
    Q_PROPERTY(u_int64_t roomCreatorID READ getRoomCreatorID)
    Q_PROPERTY(QString roomName READ getRoomName)
    Q_PROPERTY(QString taskName MEMBER name)

public:
    u_int64_t creatorID, status;
    QString name, creatorName, description, label;
    std::time_t creationTime, deadline;

    Room parent;

    QQuickItem *taskItem;

    QString getRoomName() const { return parent.name; }
    u_int64_t getRoomCreatorID() const { return parent.creatorID; }

    Task() {}

    Task(nlohmann::json task) {
        this->parent.creatorID = task.at("room creator ID");
        this->parent.name = QString::fromStdString(task.at("room name"));
        this->creatorID = task.at("creator ID");
        this->name = QString::fromStdString(task.at("name"));
        this->description = QString::fromStdString(task.at("description"));
        this->label = QString::fromStdString(task.at("label"));
        this->status = task.at("status");
        this->creationTime = task.at("creation time");
        this->deadline = task.at("deadline");
        this->creatorName = QString::fromStdString(task.at("creator name"));
    }

    // ~Task() { if(taskItem != nullptr) taskItem->deleteLater(); }

    QVariant property(const char *name) const{
        int index = staticMetaObject.indexOfProperty(name);
        if(index == -1){
            return QVariant();
        }

        return staticMetaObject.property(index).readOnGadget(this);
    }
};

struct Tasks {
    Tasks() {};
    Tasks(nlohmann::json tasks) {
        for (auto task : tasks) {
            this->tasks.append(task);
        }
    }

    Task& operator [](int i) {
        return this->tasks[i];
    }

    auto begin() {
        return this->tasks.begin();
    }

    auto end() {
        return this->tasks.end();
    }

    size_t size() {
        return this->tasks.size();
    }

    void append(Task task) {
        this->tasks.append(task);
    }
private:
    QList<Task> tasks;
};

struct Config {
    QString avatar, configuration;

    Config() = default;

    Config(nlohmann::json config) {
        this->avatar = QString::fromStdString(config.at("avatar"));
        this->configuration = QString::fromStdString(config.at("configuration"));
    }
};

enum DATA_BASE_EXECUTION_STATUS {
    //Global part
    DATA_BASE_COMPLETED_SUCCESSFULY,
    DATA_BASE_FAILED,

    //Profile part
    DATA_BASE_PROFILE_WITH_SUCH_LOGIN_IS_ALREADY_EXIST,
    DATA_BASE_PROFILE_WITH_SUCH_NAME_IS_ALREADY_EXIST,
    DATA_BASE_THERE_IS_NO_PROFILE_WITH_SUCH_NAME,
    DATA_BASE_THERE_IS_NO_PROFILE_WITH_SUCH_ID,
    DATA_BASE_THERE_IS_NO_PROFILE_WITH_SUCH_LOGIN_AND_PASSWORD,
    DATA_BASE_THERE_IS_NO_CONFIG_WITH_SUCH_PROFILE_ID,
    DATA_BASE_UNKNOWN_PROFILE,

    //Room part
    DATA_BASE_ROOM_CREATION_FAILED,
    DATA_BASE_THERE_IS_NO_ROOM_WITH_SUCH_PARAMETERS,
    DATA_BASE_ROOM_WITH_SUCH_PARAMETERS_IS_ALREADY_EXIST,
    DATA_BASE_THIS_PROFILE_IS_ALREADY_EXIST_IN_THIS_ROOM,
    DATA_BASE_ROOM_ACCESS_ERROR,

    //Task part
    DATA_BASE_TASK_CREATION_FAILED,
    DATA_BASE_THERE_IS_NO_TASK_WITH_SUCH_PARAMETERS,
    DATA_BASE_TASK_WITH_SUCH_PARAMETERS_IS_ALREADY_EXIST,
    DATA_BASE_THIS_PROFILE_IS_ALREADY_ASSIGNEE_TO_THIS_TASK,
    DATA_BASE_THIS_ID_IS_NOT_ASSIGNEE_THIS_TASK,
    DATA_BASE_THIS_PROFILE_IS_ALREADY_REVIEW_THIS_TASK,
    DATA_BASE_THIS_ID_IS_NOT_REVIEW_THIS_TASK,

    //Join part
};
enum JWT_EXECUTION_STATUS {
    JWT_COMPLETED_SUCCESSFULY,
    JWT_DECODING_FILED,
    JWT_NO_TOKEN_HEADER,
    JWT_TIME_LIMIT_EXECEEDED,
    JWT_CREATION_FAILED,
};
enum FILE_PARSER_EXECUTION_STATUS {
    FILE_PARSER_COMPLETED_SUCCESSFULY,
    FILE_PARSER_FAILED,

    FILE_PARSER_FILE_NOT_FOUND,
    FILE_PARSER_READING_DATA_ERROR,
    FILE_PARSER_WRITING_DATA_ERROR,
};

constexpr size_t DATA_BASE_BITS_COUNT{5};
constexpr size_t JWT_BITS_COUNT{3};
constexpr size_t FILE_PARSER_BITS_COUNT{3};

struct ServerStatus {
    int status;
    DATA_BASE_EXECUTION_STATUS data_base_status;
    JWT_EXECUTION_STATUS JWT_status;
    FILE_PARSER_EXECUTION_STATUS file_parse_status;

    ServerStatus(int status) {
        this->status = status;

        data_base_status = DATA_BASE_EXECUTION_STATUS(applyMask(status, DATA_BASE_BITS_COUNT, 0));
        JWT_status = JWT_EXECUTION_STATUS(applyMask(status, JWT_BITS_COUNT, DATA_BASE_BITS_COUNT));
        file_parse_status = FILE_PARSER_EXECUTION_STATUS(applyMask(status, FILE_PARSER_BITS_COUNT, DATA_BASE_BITS_COUNT + JWT_BITS_COUNT));
    }
private:
    int applyMask(int number, int bitCount, int bitShift) {
        int mask = 1;

        for (int i = 1; i < bitCount; ++i) {
            mask = (mask << 1) + 1;
        }

        mask <<= bitShift;

        return (number & mask) >> bitShift;
    }
};

#endif // CONTENT_STRUCTURES_H
