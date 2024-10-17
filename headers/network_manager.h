#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <functional>
#include <nlohmann/json.hpp>
#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QPair>
#include <QUrlQuery>

#include "content_structures.h"

class MainApplication;

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    QByteArray token;

    explicit NetworkManager(MainApplication *app = nullptr);

    QNetworkRequest* createRequest(QString domain, QString header, QByteArray &data);

    Q_INVOKABLE void sendProfileCreationRequest(QString name, QString login, QString password);
    Q_INVOKABLE void sendRoomCreationRequest(QString roomName);
    Q_INVOKABLE void sendTaskCreationRequest(QString taskName, QString room_name, QString owner_id);

    Q_INVOKABLE void sendProfileDeletingRequest();
    Q_INVOKABLE void sendRoomDeletingRequest(RoomInfo &room);
    Q_INVOKABLE void sendTaskDeletingRequest(RoomInfo &room, TaskInfo &task);

    Q_INVOKABLE void sendRoomGettingRequest(QString creatorID, QString label);
    Q_INVOKABLE void sendGettingUserRoomsRequest();
    Q_INVOKABLE void sendGettingUserTasksRequest();
    Q_INVOKABLE void sendGettingRoomTasksRequest(RoomInfo &room);
    Q_INVOKABLE void sendGettingRoomUsersRequest(RoomInfo &room);

    Q_INVOKABLE void sendAuthorizationRequest(QString login, QString password);
    void sendAuthenticationRequest();

signals:
    void authorizationResponseAccept(bool success);
    void gotRooms(QList<RoomInfo*> rooms_info);
    void roomCreated(RoomInfo*);
    void gotTasks(QList<TaskInfo*> tasks_info);
    void roomCreationFailed();
    void gotTask(TaskInfo *task);
    void taskCreationFailed();
    void gotRoom(RoomInfo* ri);

public slots:
    void handleProfileCreationResponse();
    void handleRoomCreationResponse();
    void handleTaskCreationResponse();

    void handleRoomDeletingResponse();
    void handleTaskDeletingResponse();

    void handleRoomGettingResponse();
    void handleGettingUserRoomsResponse();
    void handleGettingUserTasksResponse();
    void handleGettingRoomTasksResponse();
    void handleGettingRoomUsersResponse();

    void handleAuthenticationResponse();
    void handleAuthorizationResponse();

private:
    std::function<void(bool)> authenticationHandler;
    QNetworkAccessManager m_networkManager;
    MainApplication *app;
    QList<QNetworkReply*> m_replyList;
    static const QString host;
};

#endif // NETWORK_MANAGER_H
