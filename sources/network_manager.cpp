#include "network_manager.h"
#include "main_application.h"
#include <iostream>

//FIELDS


const QString NetworkManager::host("http://localhost:8080/");


//METHODS


NetworkManager* NetworkManager::getInstance() {
    static NetworkManager netManager;
    return &netManager;
}


//REQUESTS


//GET


//Loggining
void NetworkManager::sendLogginRequest(QString login, QString password)
{
    QNetworkRequest request(host + "LogginProfile/");

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("login", login.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("password", password.toStdString()));

    QNetworkReply *reply = networkManager.get(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleLogginResponse);

    qInfo() << "\nsend authorization request on "
                        << request.url()
                        << " with data: "
                        << requestBody.dump();
}

void NetworkManager::sendProfileAuthenticationRequest() {
    QNetworkRequest request(host + "ProfileAuthentication/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    QNetworkReply *reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleProfileAuthenticationResponse);

    qInfo() << "\nsend authentication request on "
                        << request.url()
                        << " with header: "
                        << this->jwt;
}

//Profile
void NetworkManager::sendGetProfileRequest() {
    QNetworkRequest request(host + "GetProfile/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    QNetworkReply *reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleGetProfileResponse);

    qInfo() << "\nsend profile getting request on "
                        << request.url()
                        << " with header: "
                        << this->jwt;
}

void NetworkManager::sendGetProfilesWithSubstrRequest(QString substr, u_int64_t offset) {
    QNetworkRequest request(host + "GetProfilesWithSubstr/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("substr", substr.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("offset", offset));

    QNetworkReply *reply = networkManager.get(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleGetProfilesWithSubstrResponse);

    qInfo() << "\nsend profiles with substr request on "
                        << request.url()
                        << " with body: "
                        << requestBody.dump()
                        << "\nwith header: "
                        << this->jwt;
}

void NetworkManager::sendGetPublicProfileRequest(u_int64_t profileID) {
    QNetworkRequest request(host + "GetPublicProfile/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    QNetworkReply *reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleGetPublicProfileResponse);

    qInfo() << "\nsend public profile getting request on "
                        << request.url()
                        << " with header: "
                        << this->jwt;
}

void NetworkManager::sendGetProfileConfigRequest() {
    QNetworkRequest request(host + "GetProfileConfig/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    QNetworkReply *reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleGetProfileConfigResponse);

    qInfo() << "\nsend profile config getting request on "
                        << request.url()
                        << " with header: "
                        << this->jwt;
}

void NetworkManager::sendGetProfileRoomsRequest() {
    QNetworkRequest request(host + "GetProfileRooms/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    QNetworkReply *reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleGetProfileRoomsResponse);

    qInfo() << "\nsend profile rooms getting request on "
                        << request.url()
                        << " with header: "
                        << this->jwt;
}

void NetworkManager::sendGetProfileTasksRequest() {
    QNetworkRequest request(host + "GetProfileTasks/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    QNetworkReply *reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleGetProfileTasksResponse);

    qInfo() << "\nsend profile tasks getting request on "
                        << request.url()
                        << " with header: "
                        << this->jwt;
}

void NetworkManager::sendGetProfileAssignedTasksRequest() {
    QNetworkRequest request(host + "GetProfileAssignedTasks/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    QNetworkReply *reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleGetProfileAssignedTasksResponse);

    qInfo() << "\nsend profile assigned tasks getting request on "
                        << request.url()
                        << " with header: "
                        << this->jwt;
}

void NetworkManager::sendGetProfileReviewedTasksRequest() {
    QNetworkRequest request(host + "GetProfileReviewedTasks/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    QNetworkReply *reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleGetProfileReviewedTasksResponse);

    qInfo() << "\nsend profile reviewed tasks getting request on "
                        << request.url()
                        << " with header: "
                        << this->jwt;
}

void NetworkManager::sendGetProfileReceivedInvitesRequest() {
    QNetworkRequest request(host + "GetProfileReceivedInvites/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    QNetworkReply *reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleGetProfileReceivedInvitesResponse);

    qInfo() << "\nsend profile received invites getting  request on "
            << request.url()
            << " with header: "
            << this->jwt;
}

void NetworkManager::sendGetProfileSendedInvitesRequest() {
    QNetworkRequest request(host + "GetProfileSendedInvites/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    QNetworkReply *reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleGetProfileSendedInvitesResponse);

    qInfo() << "\nsend profile sended invites getting request on "
            << request.url()
            << " with header: "
            << this->jwt;
}

//Room
void NetworkManager::sendGetRoomRequest(u_int64_t roomCreatorID, QString roomName) {
    QNetworkRequest request(host + "GetRoom/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("room creator ID", roomCreatorID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));

    QNetworkReply *reply = networkManager.get(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleGetRoomResponse);

    qInfo() << "\nsend room getting request on "
                        << request.url()
                        << " with body: "
                        << requestBody.dump()
                        << "\nwith header: "
                        << this->jwt;
}

void NetworkManager::sendGetRoomTasksRequest(u_int64_t roomCreatorID, QString roomName) {
    QNetworkRequest request(host + "GetRoomTasks/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("room creator ID", roomCreatorID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));

    QNetworkReply *reply = networkManager.get(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleGetRoomTasksResponse);

    qInfo() << "\nsend room tasks getting request on "
                        << request.url()
                        << " with body: "
                        << requestBody.dump()
                        << "\nwith header: "
                        << this->jwt;
}

void NetworkManager::sendGetRoomProfilesRequest(u_int64_t roomCreatorID, QString roomName) {
    QNetworkRequest request(host + "GetRoomProfiles/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("room creator ID", roomCreatorID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));

    QNetworkReply *reply = networkManager.get(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleGetRoomProfilesResponse);

    qInfo() << "\nsend room profiles getting request on "
                        << request.url()
                        << " with body: "
                        << requestBody.dump()
                        << "\nwith header: "
                        << this->jwt;
}

//Task


//POST


//Profile
void NetworkManager::sendCreateProfileRequest(QString name,
                                              QString login,
                                              QString password,
                                              QString email,
                                              QString phone) {
    QNetworkRequest request(host + "CreateProfile/");

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("name", name.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("login", login.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("password", password.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("email", email.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("phone", phone.toStdString()));

    QNetworkReply *reply = networkManager.post(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleCreateProfileResponse);

    qInfo() << "\nsend profile creation request on "
                        << request.url()
                        << " with data: "
                        << requestBody.dump();
}

//Room
void NetworkManager::sendCreateRoomRequest(QString roomName, QString description) {
    QNetworkRequest request(host + "CreateRoom/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("description", description.toStdString()));

    QNetworkReply *reply = networkManager.post(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleCreateRoomResponse);

    qInfo() << "\nsend room creation request on "
                        << request.url()
                        << " with data: "
                        << requestBody.dump()
                        << "\nwith header: "
                        << this->jwt;
}

void NetworkManager::sendAppendMemberToRoomRequest(u_int64_t memberID,
                                                   u_int64_t roomCreatorID,
                                                   QString roomName) {
    QNetworkRequest request(host + "AppendMemberToRoom/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("member ID", memberID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room creator ID", roomCreatorID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));

    QNetworkReply *reply = networkManager.post(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleAppendMemberToRoomResponse);

    qInfo() << "\nsend append member to room request on "
                        << request.url()
                        << " with data: "
                        << requestBody.dump()
                        << "\nwith header: "
                        << this->jwt;
}

void NetworkManager::sendDeleteRoomRequest(u_int64_t roomCreatorID, QString roomName) {
    QNetworkRequest request(host + "DeleteRoom/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("room creator ID", roomCreatorID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));

    QNetworkReply *reply = networkManager.post(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleDeleteRoomResponse);

    qInfo() << "\nsend room deleting request on "
                        << request.url()
                        << " with body: "
                        << requestBody.dump()
                        << "\nwith header: "
                        << this->jwt;
}

//Task
void NetworkManager::sendCreateTaskRequest(u_int64_t roomCreatorID,
                                           QString roomName,
                                           QString taskName,
                                           QString description,
                                           QString label,
                                           u_int64_t status,
                                           u_int64_t timeToLive) {
    QNetworkRequest request(host + "CreateTask/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("room creator ID", roomCreatorID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("task name", taskName.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("description", description.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("label", label.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("status", status));
    requestBody.push_back(nlohmann::json::object_t::value_type("time to live", timeToLive));

    QNetworkReply *reply = networkManager.post(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleCreateTaskResponse);

    qInfo() << "\nsend task creation request on "
                        << request.url()
                        << " with data: "
                        << requestBody.dump()
                        << "\nwith header: "
                        << this->jwt;
}

void NetworkManager::sendAddTaskToAssigneeRequest(u_int64_t roomCreatorID,
                                              QString roomName,
                                              QString taskName,
                                              u_int64_t assigneeID) {
    QNetworkRequest request(host + "AddTaskToAssignee/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("room creator ID", roomCreatorID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("task name", taskName.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("assignee ID", assigneeID));


    QNetworkReply *reply = networkManager.post(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleAddTaskToAssigneeResponse);

    qInfo() << "\nsend add task to assignee request on "
                        << request.url()
                        << " with data: "
                        << requestBody.dump()
                        << "\nwith header: "
                        << this->jwt;
}

void NetworkManager::sendAddTaskToReviewerRequest(u_int64_t roomCreatorID,
                                              QString roomName,
                                              QString taskName,
                                              u_int64_t reviewerID) {
    QNetworkRequest request(host + "AddTaskToReviewer/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("room creator ID", roomCreatorID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("task name", taskName.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("reviewer ID", reviewerID));


    QNetworkReply *reply = networkManager.post(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleAddTaskToReviewerResponse);

    qInfo() << "\nsend add task to reviewer request on "
                        << request.url()
                        << " with data: "
                        << requestBody.dump()
                        << "\nwith header: "
                        << this->jwt;
}

void NetworkManager::sendRemoveTaskFromAssigneeRequest(u_int64_t roomCreatorID,
                                                   QString roomName,
                                                   QString taskName,
                                                   u_int64_t assigneeID) {
    QNetworkRequest request(host + "RemoveTaskFromAssignee/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("room creator ID", roomCreatorID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("task name", taskName.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("assignee ID", assigneeID));


    QNetworkReply *reply = networkManager.post(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleRemoveTaskFromAssigneeResponse);

    qInfo() << "\nsend remove task from assignee request on "
                        << request.url()
                        << " with data: "
                        << requestBody.dump()
                        << "\nwith header: "
                        << this->jwt;
}

void NetworkManager::sendRemoveTaskFromReviewerRequest(u_int64_t roomCreatorID,
                                                   QString roomName,
                                                   QString taskName,
                                                   u_int64_t reviewerID) {
    QNetworkRequest request(host + "RemoveTaskFromReviewer/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("room creator ID", roomCreatorID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("task name", taskName.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("reviewer ID", reviewerID));


    QNetworkReply *reply = networkManager.post(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleRemoveTaskFromReviewerResponse);

    qInfo() << "\nsend remove task from reviewer request on "
                        << request.url()
                        << " with data: "
                        << requestBody.dump()
                        << "\nwith header: "
                        << this->jwt;
}

void NetworkManager::sendDeleteTaskRequest(u_int64_t roomCreatorID, QString roomName, QString taskName) {
    QNetworkRequest request(host + "DeleteTask/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("room creator ID", roomCreatorID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));
    requestBody.push_back(nlohmann::json::object_t::value_type("task name", taskName.toStdString()));

    QNetworkReply *reply = networkManager.post(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleDeleteTaskResponse);

    qInfo() << "\nsend room deleting request on "
                        << request.url()
                        << " with body: "
                        << requestBody.dump()
                        << "\nwith header: "
                        << this->jwt;
}

//Invites
void NetworkManager::sendCreateInviteRequest(u_int64_t receiverID,
                                             u_int64_t roomCreatorID,
                                             QString roomName) {
    QNetworkRequest request(host + "CreateInvite/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("receiver ID", receiverID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room creator ID", roomCreatorID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));

    QNetworkReply *reply = networkManager.post(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleCreateInviteResponse);

    qInfo() << "\nsend create invite request on "
            << request.url()
            << " with body: "
            << requestBody.dump()
            << "\nwith header: "
            << this->jwt;
}

void NetworkManager::sendAcceptInviteRequest(u_int64_t roomCreatorID,
                                             QString roomName) {
    QNetworkRequest request(host + "AcceptInvite/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("room creator ID", roomCreatorID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));

    QNetworkReply *reply = networkManager.post(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleAcceptInviteResponse);

    qInfo() << "\nsend accept invite request on "
            << request.url()
            << " with body: "
            << requestBody.dump()
            << "\nwith header: "
            << this->jwt;
}

void NetworkManager::sendDeleteSendedInviteRequest(u_int64_t receiverID,
                                                   u_int64_t roomCreatorID,
                                                   QString roomName) {
    QNetworkRequest request(host + "DeleteSendedInvite/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("receiver ID", receiverID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room creator ID", roomCreatorID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));

    QNetworkReply *reply = networkManager.post(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleDeleteSendedInviteResponse);

    qInfo() << "\nsend delete sended invite request on "
            << request.url()
            << " with body: "
            << requestBody.dump()
            << "\nwith header: "
            << this->jwt;
}

void NetworkManager::sendDeleteReceivedInviteRequest(u_int64_t senderID,
                                                     u_int64_t roomCreatorID,
                                                     QString roomName) {
    QNetworkRequest request(host + "DeleteReceivedInvite/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    nlohmann::json requestBody;
    requestBody.push_back(nlohmann::json::object_t::value_type("sender ID", senderID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room creator ID", roomCreatorID));
    requestBody.push_back(nlohmann::json::object_t::value_type("room name", roomName.toStdString()));

    QNetworkReply *reply = networkManager.post(request, requestBody.dump().c_str());

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleDeleteReceivedInviteResponse);

    qInfo() << "\nsend delete received invite request on "
            << request.url()
            << " with body: "
            << requestBody.dump()
            << "\nwith header: "
            << this->jwt;
}


//DELETE


//Profile
void NetworkManager::sendDeleteProfileRequest()
{
    QNetworkRequest request(host + "DeleteProfile/");

    request.setRawHeader(QByteArray("Authorization"), this->jwt);

    QNetworkReply *reply = networkManager.deleteResource(request);

    connect(reply, &QNetworkReply::finished, this, &NetworkManager::handleDeleteProfileResponse);

    qInfo() << "\nsend profile deleting request on "
                        << request.url()
                        << " with header: "
                        << this->jwt;
}

//Room

//Task


//PATCH


//Profile

//Room

//Task





//HANDLERS


//GET


//Loggining
void NetworkManager::handleLogginResponse()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "profile loggining server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        std::string jwt = response.at("JWT");

        emit NetworkManager::finishLogginResponseHandling(serverStatus, jwt.c_str());
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleProfileAuthenticationResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "profile authenticate server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");

        emit NetworkManager::finishProfileAuthenticationResponseHandling(serverStatus);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

//Profile
void NetworkManager::handleGetProfileResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "get profile server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump();

        int serverStatus = response.at("status");
        Models::Profile profile = response.at("profile");

        emit finishGetProfileResponseHandling(serverStatus, profile);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleGetProfilesWithSubstrResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "get profiles with substr server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Profiles profiles = response.at("profiles");

        emit finishGetProfilesWithSubstrHandling(serverStatus, profiles);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleGetPublicProfileResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "get public profile server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Profile profile = response.at("profile");

        emit finishGetPublicProfileResponseHandling(serverStatus, profile);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleGetProfileConfigResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "get profile config server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Config config = response.at("config");

        emit finishGetProfileConfigResponseHandling(serverStatus, config);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleGetProfileRoomsResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "get profile rooms server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Rooms rooms = response.at("rooms");

        emit finishGetProfileRoomsResponseHandling(serverStatus, rooms);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleGetProfileTasksResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "get profile tasks server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Tasks tasks = response.at("tasks");

        emit finishGetProfileTasksResponseHandling(serverStatus, tasks);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleGetProfileAssignedTasksResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "get profile assigned tasks server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Tasks tasks = response.at("tasks");

        emit finishGetProfileTasksResponseHandling(serverStatus, tasks);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleGetProfileReviewedTasksResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "get profile reviewed tasks server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Tasks tasks = response.at("tasks");

        emit finishGetProfileTasksResponseHandling(serverStatus, tasks);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleGetProfileReceivedInvitesResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "get profile reveived invites server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Invites invites = response.at("invites");
        invites.setType(Models::RECEIVED);

        emit finishGetProfileReceivedInvitesResponseHandling(serverStatus, invites);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleGetProfileSendedInvitesResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "get profile sended invites server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Invites invites = response.at("invites");
        invites.setType(Models::SENDED);

        emit finishGetProfileSendedInvitesResponseHandling(serverStatus, invites);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}


//Room
void NetworkManager::handleGetRoomResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "get room server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Room room = response.at("room");

        emit finishGetRoomResponseHandling(serverStatus, room);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleGetRoomTasksResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "get room tasks server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Tasks tasks = response.at("tasks");

        emit this->finishGetRoomTasksResponseHandling(serverStatus, tasks);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}


void NetworkManager::handleGetRoomProfilesResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "get room profiles server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Profiles profiles = response.at("profiles");

        emit finishGetRoomProfilesResponseHandling(serverStatus, profiles);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

//Task


//POST


//Profile
void NetworkManager::handleCreateProfileResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "create profile server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        std::string jwt = response.at("JWT");

        emit NetworkManager::finishCreateProfileHandling(serverStatus, jwt.c_str());
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

//Room
void NetworkManager::handleCreateRoomResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "create room server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Room room = response.at("room");

        emit finishCreateRoomResponseHandling(serverStatus, room);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleAppendMemberToRoomResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "append member to room server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");

        emit finishAppendMemberToRoomResponseHandling(serverStatus);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleDeleteRoomResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "delete room server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");

        emit finishDeleteRoomResponseHandling(serverStatus);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

//Task
void NetworkManager::handleCreateTaskResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "create task server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Task task = response.at("task");

        emit finishCreateTaskResponseHandling(serverStatus, task);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleAddTaskToAssigneeResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "add task to aasignee server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");

        emit finishAddTaskToAssigneeResponseHandling(serverStatus);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleAddTaskToReviewerResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "add task to reviewer server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");

        emit finishAddTaskToReviewerResponseHandling(serverStatus);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleRemoveTaskFromAssigneeResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "remove task from assignee server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");

        emit finishAddTaskToReviewerResponseHandling(serverStatus);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleRemoveTaskFromReviewerResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "remove task from reviewer server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");

        emit finishAddTaskToReviewerResponseHandling(serverStatus);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleDeleteTaskResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "delete task server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");

        emit finishAddTaskToReviewerResponseHandling(serverStatus);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

//Invite
void NetworkManager::handleCreateInviteResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "create invite server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Invite invite = response.at("invite");
        invite.type = Models::SENDED;

        emit finishCreateInviteResponseHandling(serverStatus, invite);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleAcceptInviteResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "accept invite server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Invite invite = response.at("invite");
        invite.type = Models::RECEIVED;

        emit finishAcceptInviteResponseHandling(serverStatus, invite);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleDeleteSendedInviteResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "delete sended invite server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Invite invite = response.at("invite");        
        invite.type = Models::SENDED;

        emit finishDeleteSendedInviteResponseHandling(serverStatus, invite);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

void NetworkManager::handleDeleteReceivedInviteResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "delete received invite server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");
        Models::Invite invite = response.at("invite");
        invite.type = Models::RECEIVED;

        emit finishDeleteReceivedInviteResponseHandling(serverStatus, invite);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

//DELETE


//Profile
void NetworkManager::handleDeleteProfileResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "delete profile server response: ";

    try {
        nlohmann::json response = nlohmann::json::parse(reply->readAll());
        qInfo() << response.dump().c_str();

        int serverStatus = response.at("status");

        emit finishDeleteProfileResponseHandling(serverStatus);
    } catch (nlohmann::json::exception &exception) {
        qInfo() << exception.what();
        return;
    }

    reply->deleteLater();
}

//Room

//Task


//PATCH


//Profile

//Room

//Task
