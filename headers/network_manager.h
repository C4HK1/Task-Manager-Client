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

#include "models.h"

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
    void finishLogginResponseHandling(Models::ServerStatus serverStatus, QByteArray jwt);
    void finishProfileAuthenticationResponseHandling(Models::ServerStatus serverStatus);

    //Profile
    void finishGetProfileResponseHandling(Models::ServerStatus serverStatus, Models::Profile profile);
    void finishGetProfilesWithPrefixHandling(Models::ServerStatus serverStatus, Models::Profiles profiles);
    void finishGetPublicProfileResponseHandling(Models::ServerStatus serverStatus, Models::Profile profile);
    void finishGetProfileConfigResponseHandling(Models::ServerStatus serverStatus, Models::Config config);
    void finishGetProfileRoomsResponseHandling(Models::ServerStatus serverStatus, Models::Rooms rooms);
    void finishGetProfileTasksResponseHandling(Models::ServerStatus serverStatus, Models::Tasks tasks);
    void finishGetProfileAssignedTasksResponseHandling(Models::ServerStatus serverStatus, Models::Tasks tasks);
    void finishGetProfileReviewedTasksResponseHandling(Models::ServerStatus serverStatus, Models::Tasks tasks);

    //Room
    void finishGetRoomResponseHandling(Models::ServerStatus serverStatus, Models::Room room);
    void finishGetRoomTasksResponseHandling(Models::ServerStatus serverStatus, Models::Tasks tasks);
    void finishGetRoomProfilesResponseHandling(Models::ServerStatus serverStatus, Models::Profiles profiles);

    //Task

//POST
    //Profile
    void finishCreateProfileHandling(Models::ServerStatus serverStatus, QByteArray jwt);

    //Room
    void finishCreateRoomResponseHandling(Models::ServerStatus serverStatus, Models::Room room);
    void finishAppendMemberToRoomResponseHandling(Models::ServerStatus serverStatus);
    void finishDeleteRoomResponseHandling(Models::ServerStatus serverStatus);

    //Task
    void finishCreateTaskResponseHandling(Models::ServerStatus serverStatus, Models::Task task);
    void finishAddTaskToAssigneeResponseHandling(Models::ServerStatus serverStatus);
    void finishAddTaskToReviewerResponseHandling(Models::ServerStatus serverStatus);
    void finishRemoveTaskFromAssigneeResponseHandling(Models::ServerStatus serverStatus);
    void finishRemoveTaskFromReviewerResponseHandling(Models::ServerStatus serverStatus);
    void finishDeleteTaskResponseHandling(Models::ServerStatus serverStatus);

//DELETE
    //Profile
    void finishDeleteProfileResponseHandling(Models::ServerStatus serverStatus);

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
protected:
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
