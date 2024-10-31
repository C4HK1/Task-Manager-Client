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

class NetworkManager : public QObject
{
    Q_OBJECT
public:
//REQUESTS

//GET
    //Logginning
    Q_INVOKABLE void sendLogginRequest(QString login, QString password);
    void sendProfileAuthenticationRequest();

    //Profile
    Q_INVOKABLE void sendGetProfileRequest();
    Q_INVOKABLE void sendGetProfilesWithPrefixRequest(QString prefix);
    Q_INVOKABLE void sendGetPublicProfileRequest(u_int64_t profileID);
    Q_INVOKABLE void sendGetProfileConfigRequest();
    Q_INVOKABLE void sendGetProfileRoomsRequest();
    Q_INVOKABLE void sendGetProfileTasksRequest();
    Q_INVOKABLE void sendGetProfileAssignedTasksRequest();
    Q_INVOKABLE void sendGetProfileReviewedTasksRequest();

    //Room
    Q_INVOKABLE void sendGetRoomRequest(u_int64_t roomCreatorID, QString roomName);
    Q_INVOKABLE void sendGetRoomTasksRequest(u_int64_t roomCreatorID, QString roomName);
    Q_INVOKABLE void sendGetRoomProfilesRequest(u_int64_t roomCreatorID, QString roomName);

    //Task

//POST
    //Profile
    Q_INVOKABLE void sendCreateProfileRequest(QString name,
                                                QString login,
                                                QString password,
                                                QString email,
                                                QString phone);

    //Room
    Q_INVOKABLE void sendCreateRoomRequest(QString roomName, QString description);
    Q_INVOKABLE void sendAppendMemberToRoomRequest(u_int64_t memberID,
                                                   u_int64_t roomCreatorID,
                                                   QString roomName);
    Q_INVOKABLE void sendDeleteRoomRequest(u_int64_t roomCreatorID, QString roomName);

    //Task
    Q_INVOKABLE void sendCreateTaskRequest(u_int64_t roomCreatorID,
                                             QString roomName,
                                             QString taskName,
                                             QString description,
                                             QString label,
                                             u_int64_t status,
                                             u_int64_t timeToLive);
    Q_INVOKABLE void sendAddTaskToAssigneeRequest(u_int64_t roomCreatorID,
                                                  QString roomName,
                                                  QString taskName,
                                                  u_int64_t assigneeID);
    Q_INVOKABLE void sendAddTaskToReviewerRequest(u_int64_t roomCreatorID,
                                                  QString roomName,
                                                  QString taskName,
                                                  u_int64_t reviewerID);
    Q_INVOKABLE void sendRemoveTaskFromAssigneeRequest(u_int64_t roomCreatorID,
                                                       QString roomName,
                                                       QString taskName,
                                                       u_int64_t assigneeID);
    Q_INVOKABLE void sendRemoveTaskFromReviewerRequest(u_int64_t roomCreatorID,
                                                       QString roomName,
                                                       QString taskName,
                                                       u_int64_t reviewerID);
    Q_INVOKABLE void sendDeleteTaskRequest(u_int64_t roomCreatorID,
                                             QString roomName,
                                             QString taskName);

//DELETE
    //Profile
    Q_INVOKABLE void sendDeleteProfileRequest();

    //Room

    //Task

//PATCH
    //Profile

    //Room

    //Task


//FIELDS
    QByteArray jwt;


//METHODS
    static NetworkManager* getInstance();

    QNetworkRequest* createRequest(QString domain,
                                   QString header,
                                   QByteArray &data);


signals:
//SIGNALS

//GET
    //Logginning
    void finishLogginResponseHandling(ServerStatus serverStatus, QByteArray jwt);
    void finishProfileAuthenticationResponseHandling(ServerStatus serverStatus);

    //Profile
    void finishGetProfileResponseHandling(ServerStatus serverStatus, Profile profile);
    void finishGetProfilesWithPrefixHandling(ServerStatus serverStatus, Profiles profiles);
    void finishGetPublicProfileResponseHandling(ServerStatus serverStatus, Profile profile);
    void finishGetProfileConfigResponseHandling(ServerStatus serverStatus, Config config);
    void finishGetProfileRoomsResponseHandling(ServerStatus serverStatus, Rooms rooms);
    void finishGetProfileTasksResponseHandling(ServerStatus serverStatus, Tasks tasks);
    void finishGetProfileAssignedTasksResponseHandling(ServerStatus serverStatus, Tasks tasks);
    void finishGetProfileReviewedTasksResponseHandling(ServerStatus serverStatus, Tasks tasks);

    //Room
    void finishGetRoomResponseHandling(ServerStatus serverStatus, Room room);
    void finishGetRoomTasksResponseHandling(ServerStatus serverStatus, Tasks tasks);
    void finishGetRoomProfilesResponseHandling(ServerStatus serverStatus, Profiles profiles);

    //Task

//POST
    //Profile
    void finishCreateProfileHandling(ServerStatus serverStatus, QByteArray jwt);

    //Room
    void finishCreateRoomResponseHandling(ServerStatus serverStatus, Room room);
    void finishAppendMemberToRoomResponseHandling(ServerStatus serverStatus);
    void finishDeleteRoomResponseHandling(ServerStatus serverStatus);

    //Task
    void finishCreateTaskResponseHandling(ServerStatus serverStatus, Task task);
    void finishAddTaskToAssigneeResponseHandling(ServerStatus serverStatus);
    void finishAddTaskToReviewerResponseHandling(ServerStatus serverStatus);
    void finishRemoveTaskFromAssigneeResponseHandling(ServerStatus serverStatus);
    void finishRemoveTaskFromReviewerResponseHandling(ServerStatus serverStatus);
    void finishDeleteTaskResponseHandling(ServerStatus serverStatus);

//DELETE
    //Profile
    void finishDeleteProfileResponseHandling(ServerStatus serverStatus);

    //Room

    //Task

//PATCH
    //Profile

    //Room

    //Task


public slots:
//HANDLERS

//GET
    //Logginning
    void handleLogginResponse();
    void handleProfileAuthenticationResponse();

    //Profile
    void handleGetProfileResponse();
    void handleGetProfilesWithPrefixResponse();
    void handleGetPublicProfileResponse();
    void handleGetProfileConfigResponse();
    void handleGetProfileRoomsResponse();
    void handleGetProfileTasksResponse();
    void handleGetProfileAssignedTasksResponse();
    void handleGetProfileReviewedTasksResponse();

    //Room
    void handleGetRoomResponse();
    void handleGetRoomTasksResponse();
    void handleGetRoomProfilesResponse();

    //Task

//POST
    //Profile
    void handleCreateProfileResponse();

    //Room
    void handleCreateRoomResponse();
    void handleAppendMemberToRoomResponse();
    void handleDeleteRoomResponse();

    //Task
    void handleCreateTaskResponse();
    void handleAddTaskToAssigneeResponse();
    void handleAddTaskToReviewerResponse();
    void handleRemoveTaskFromAssigneeResponse();
    void handleRemoveTaskFromReviewerResponse();
    void handleDeleteTaskResponse();

//DELETE
    //Profile
    void handleDeleteProfileResponse();

    //Room

    //Task

//PATCH
    //Profile

    //Room

    //Task


private:
    NetworkManager() {}
    NetworkManager(const NetworkManager&) = delete;

    NetworkManager& operator=(const NetworkManager&) = delete;

    std::function<void(bool)> authenticationHandler;
    QNetworkAccessManager networkManager;
    QList<QNetworkReply*> replyList;
    static const QString host;
};

#endif // NETWORK_MANAGER_H
