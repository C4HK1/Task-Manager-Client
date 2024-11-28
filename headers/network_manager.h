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
    Q_INVOKABLE void sendGetProfilesWithSubstrRequest(QString substr, u_int64_t offset);
    Q_INVOKABLE void sendGetPublicProfileRequest(u_int64_t profileID);
    Q_INVOKABLE void sendGetProfileConfigRequest();
    Q_INVOKABLE void sendGetProfileRoomsRequest();
    Q_INVOKABLE void sendGetProfileTasksRequest();
    Q_INVOKABLE void sendGetProfileAssignedTasksRequest();
    Q_INVOKABLE void sendGetProfileReviewedTasksRequest();
    Q_INVOKABLE void sendGetProfileReceivedInvitesRequest();
    Q_INVOKABLE void sendGetProfileSendedInvitesRequest();


    //Room
    Q_INVOKABLE void sendGetRoomRequest(u_int64_t roomCreatorID, QString roomName);
    Q_INVOKABLE void sendGetRoomTasksRequest(u_int64_t roomCreatorID, QString roomName);
    Q_INVOKABLE void sendGetRoomProfilesRequest(u_int64_t roomCreatorID, QString roomName);

    //Task
    Q_INVOKABLE void sendGetTaskAssignees(u_int64_t roomCreatorID, QString roomName, QString taskName);
    Q_INVOKABLE void sendGetTaskReviewers(u_int64_t roomCreatorID, QString roomName, QString taskName);

    //Invite

//POST
    //Profile
    Q_INVOKABLE void sendCreateProfileRequest(QString name,
                                              QString login,
                                              QString password,
                                              QString email,
                                              QString phone);

    //Room
    Q_INVOKABLE void sendCreateRoomRequest(QString roomName, QString description);
    Q_INVOKABLE void sendLeaveFromRoomRequest(u_int64_t roomCreatorID,
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

    //Invite
    Q_INVOKABLE void sendCreateInviteRequest(u_int64_t receiverID,
                                             u_int64_t roomCreatorID,
                                             QString roomName);
    Q_INVOKABLE void sendAcceptInviteRequest(u_int64_t roomCreatorID,
                                             QString roomName);
    Q_INVOKABLE void sendDeleteSendedInviteRequest(u_int64_t receiverID,
                                                   u_int64_t roomCreatorID,
                                                   QString roomName);
    Q_INVOKABLE void sendDeleteReceivedInviteRequest(u_int64_t senderID,
                                                     u_int64_t roomCreatorID,
                                                     QString roomName);

//DELETE
    //Profile
    Q_INVOKABLE void sendDeleteProfileRequest();

    //Room

    //Task

//PATCH
    //Profile

    //Room

    //Task

    //Invite


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
    void finishGetProfilesWithSubstrHandling(Models::ServerStatus serverStatus, Models::Profiles profiles);
    void finishGetPublicProfileResponseHandling(Models::ServerStatus serverStatus, Models::Profile profile);
    void finishGetProfileConfigResponseHandling(Models::ServerStatus serverStatus, Models::Config config);
    void finishGetProfileRoomsResponseHandling(Models::ServerStatus serverStatus, Models::Rooms rooms);
    void finishGetProfileTasksResponseHandling(Models::ServerStatus serverStatus, Models::Tasks tasks);
    void finishGetProfileAssignedTasksResponseHandling(Models::ServerStatus serverStatus, Models::Tasks tasks);
    void finishGetProfileReviewedTasksResponseHandling(Models::ServerStatus serverStatus, Models::Tasks tasks);
    void finishGetProfileReceivedInvitesResponseHandling(Models::ServerStatus serverStatus, Models::Invites invites);
    void finishGetProfileSendedInvitesResponseHandling(Models::ServerStatus serverStatus, Models::Invites invites);

    //Room
    void finishGetRoomResponseHandling(Models::ServerStatus serverStatus, Models::Room room);
    void finishGetRoomTasksResponseHandling(Models::ServerStatus serverStatus, Models::Tasks tasks);
    void finishGetRoomProfilesResponseHandling(Models::ServerStatus serverStatus, Models::Profiles profiles);

    //Task
    void finishGetTaskAssigneesResponseHandling(Models::ServerStatus serverStatus, Models::Profiles profiles);
    void finishGetTaskReviewersResponseHandling(Models::ServerStatus serverStatus, Models::Profiles profiles);

    //Invite

//POST
    //Profile
    void finishCreateProfileHandling(Models::ServerStatus serverStatus, QByteArray jwt);

    //Room
    void finishCreateRoomResponseHandling(Models::ServerStatus serverStatus, Models::Room room);
    void finishLeaveFromRoomResponseHandling(Models::ServerStatus serverStatus);
    void finishDeleteRoomResponseHandling(Models::ServerStatus serverStatus);

    //Task
    void finishCreateTaskResponseHandling(Models::ServerStatus serverStatus, Models::Task task);
    void finishAddTaskToAssigneeResponseHandling(Models::ServerStatus serverStatus);
    void finishAddTaskToReviewerResponseHandling(Models::ServerStatus serverStatus);
    void finishRemoveTaskFromAssigneeResponseHandling(Models::ServerStatus serverStatus);
    void finishRemoveTaskFromReviewerResponseHandling(Models::ServerStatus serverStatus);
    void finishDeleteTaskResponseHandling(Models::ServerStatus serverStatus);

    //Invite
    void finishCreateInviteResponseHandling(Models::ServerStatus serverStatus, Models::Invite invite);
    void finishAcceptInviteResponseHandling(Models::ServerStatus serverStatus, Models::Invite invite);
    void finishDeleteSendedInviteResponseHandling(Models::ServerStatus serverStatus, Models::Invite invite);
    void finishDeleteReceivedInviteResponseHandling(Models::ServerStatus serverStatus, Models::Invite invite);

//DELETE
    //Profile
    void finishDeleteProfileResponseHandling(Models::ServerStatus serverStatus);

    //Room

    //Task

    //Invite

//PATCH
    //Profile

    //Room

    //Task

    //Invite

public slots:
//HANDLERS

//GET
    //Logginning
    void handleLogginResponse();
    void handleProfileAuthenticationResponse();

    //Profile
    void handleGetProfileResponse();
    void handleGetProfilesWithSubstrResponse();
    void handleGetPublicProfileResponse();
    void handleGetProfileConfigResponse();
    void handleGetProfileRoomsResponse();
    void handleGetProfileTasksResponse();
    void handleGetProfileAssignedTasksResponse();
    void handleGetProfileReviewedTasksResponse();
    void handleGetProfileReceivedInvitesResponse();
    void handleGetProfileSendedInvitesResponse();

    //Room
    void handleGetRoomResponse();
    void handleGetRoomTasksResponse();
    void handleGetRoomProfilesResponse();

    //Task
    void handleGetTaskAssigneesResponse();
    void handleGetTaskReviewersResponse();

    //Invite

//POST
    //Profile
    void handleCreateProfileResponse();

    //Room
    void handleCreateRoomResponse();
    void handleLeaveFromRoomResponse();
    void handleDeleteRoomResponse();

    //Task
    void handleCreateTaskResponse();
    void handleAddTaskToAssigneeResponse();
    void handleAddTaskToReviewerResponse();
    void handleRemoveTaskFromAssigneeResponse();
    void handleRemoveTaskFromReviewerResponse();
    void handleDeleteTaskResponse();

    //Invite
    void handleCreateInviteResponse();
    void handleAcceptInviteResponse();
    void handleDeleteSendedInviteResponse();
    void handleDeleteReceivedInviteResponse();

//DELETE
    //Profile
    void handleDeleteProfileResponse();

    //Room

    //Task

    //Invite

//PATCH
    //Profile

    //Room

    //Task

    //Invite
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
