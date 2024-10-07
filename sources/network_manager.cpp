#include "network_manager.h"
#include "main_application.h"

const QString NetworkManager::host("http://localhost:8080");

NetworkManager::NetworkManager(MainApplication *app) : QObject{app}, app(app) {}

void NetworkManager::sendAuthorizationRequest(QString login, QString password)
{
    QNetworkRequest request(host + "/ProfileLogining");

    QString jsonAuthInfo = QString("{\"login\": \"") + login + QString("\", \"password\": \"") + password + QString("\"}");

    QNetworkReply *m_reply = m_networkManager.get(request, jsonAuthInfo.toUtf8());
    connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleAuthorizationResponse);
    /* DEBUG */ qInfo() << QString("http get requeast was send on " + request.url().toString() + " with data: " + jsonAuthInfo);
}

void NetworkManager::handleAuthorizationResponse()
{
    QNetworkReply *m_reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QString response(m_reply->readAll());
    m_reply->deleteLater();
    /* DEBUG */ qInfo() << QString("server response: ") + response;

    if(!QDir("data").exists()){
        QDir().mkdir("data");
    }

    QByteArray token;

    try{
        nlohmann::json jsonInfo = nlohmann::json::parse(response.toStdString());
        token = QByteArray(QString(nlohmann::to_string(jsonInfo["JWT"]).c_str()).replace("\"", "").toUtf8());

        if(token.size() > 0){
            QFile file("data/authentication_key.organizer");
            file.open(QIODevice::WriteOnly);
            file.write(token);
            file.close();

            this->token = token;
        }
    } catch (std::exception &ex) {
        qInfo() << ex.what();
    }

    sendAuthenticationRequest(token);
}

void NetworkManager::sendProfileCreationRequest(QString login, QString password)
{
    QNetworkRequest request(host + "/ProfileCreation");

    QString jsonProfileCreationBody = QString("{\"login\": \"") + login + QString("\", \"password\": \"") + password + QString("\"}");
    QNetworkReply *m_reply = m_networkManager.post(request, jsonProfileCreationBody.toUtf8());
    connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleProfileCreationResponse);
}

void NetworkManager::handleProfileCreationResponse() {
    QNetworkReply *m_reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QString response(m_reply->readAll());
    m_reply->deleteLater();
    /* DEBUG */ qInfo() << QString("server response: ") + response;

    if(!QDir("data").exists()){
        QDir().mkdir("data");
    }

    try{
        nlohmann::json jsonInfo = nlohmann::json::parse(response.toStdString());
        auto token = QByteArray(QString(nlohmann::to_string(jsonInfo["JWT"]).c_str()).replace("\"", "").toUtf8());

        if (token.size() > 0) {
            QFile file("data/authentication_key.organizer");
            file.open(QIODevice::WriteOnly);
            file.write(token);
            file.close();

            this->token = token;

            sendAuthenticationRequest(token);
        }
    } catch (std::exception &ex) {
        qInfo() << ex.what();
        return;
    }
}

void NetworkManager::sendProfileDeletingRequest()
{
    QNetworkRequest request(host + "/ProfileDeleting");
    request.setRawHeader(QByteArray("Authorization"), this->token);
    QNetworkReply *m_reply = m_networkManager.deleteResource(request);
    connect(m_reply, &QNetworkReply::finished, app, &MainApplication::outFromAccount);
}

void NetworkManager::sendAuthenticationRequest(QByteArray token) {
    QNetworkRequest request(host);
    request.setRawHeader(QByteArray("Authorization"), token);
    QNetworkReply *m_reply = m_networkManager.get(request);
    connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleAuthenticationResponse);
}

void NetworkManager::handleAuthenticationResponse() {
    QNetworkReply *m_reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QString response(m_reply->readAll());
    m_reply->deleteLater();
    /* DEBUG */ qInfo() << QString("server response: ") + response;

    try{
        nlohmann::json jsonInfo = nlohmann::json::parse(response.toStdString());
        QString status(nlohmann::to_string(jsonInfo["authorizetion info"]).c_str());

        bool result = status == "\"true\"";

        emit NetworkManager::authorizationResponseAccept(result);
    } catch (std::exception &ex) {
        qInfo() << ex.what();
        return;
    }
}

void NetworkManager::sendRoomCreationRequest(QString roomName) {
    QNetworkRequest request(host + "/RoomCreation");
    request.setRawHeader(QByteArray("Authorization"), this->token);

    QString jsonProfileCreationBody = QString("{\"room label\": \"") + roomName + QString("\"}");

    QNetworkReply *m_reply = m_networkManager.post(request, jsonProfileCreationBody.toUtf8());
    connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleRoomCreationResponse);

    qInfo() << "\"" + roomName + "\" room creation request";
}

void NetworkManager::handleRoomCreationResponse() {
    QNetworkReply *m_reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QString response(m_reply->readAll());
    m_reply->deleteLater();
    /* DEBUG */ qInfo() << QString("server response: ") + response;
}

void NetworkManager::sendTaskCretionRequest(QString &taskName, RoomInfo &room) {
    QNetworkRequest request(host + "/TaskCreation");
    request.setRawHeader(QByteArray("Authorization"), this->token);

    QString jsonProfileCreationBody = QString("{\"room label\": \"") + room.room_name + QString("\", \"room creator id\": \"") + room.owner_id + QString("\", \"task label\": \"") + taskName + QString("\"}");

    QNetworkReply *m_reply = m_networkManager.post(request, jsonProfileCreationBody.toUtf8());
    connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleTaskCreationResponse);

    qInfo() << "\"" + taskName + "\" task creation request";
}

void NetworkManager::handleTaskCreationResponse() {
    QNetworkReply *m_reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QString response(m_reply->readAll());
    m_reply->deleteLater();
    /* DEBUG */ qInfo() << QString("server response: ") + response;
}

void NetworkManager::sendRoomDeletingRequest(RoomInfo &room) {
    QNetworkRequest request(host + "/RoomDeleting");
    request.setRawHeader(QByteArray("Authorization"), this->token);

    QString jsonProfileCreationBody = QString("{\"room label\": \"") + room.room_name + QString("\", \"room creator id\": \"") + room.owner_id + QString("\"}");

    QNetworkReply *m_reply = m_networkManager.post(request, jsonProfileCreationBody.toUtf8());
    connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleRoomDeletingResponse);
}

void NetworkManager::handleRoomDeletingResponse() {
    QNetworkReply *m_reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QString response(m_reply->readAll());
    m_reply->deleteLater();
    /* DEBUG */ qInfo() << QString("server response: ") + response;
}


void NetworkManager::sendTaskDeletingRequest(RoomInfo &room, TaskInfo &task) {
    QNetworkRequest request(host + "/TaskDeleting");
    request.setRawHeader(QByteArray("Authorization"), this->token);

    QString jsonProfileCreationBody = QString("{\"room label\": \"") + room.room_name + QString("\", \"room creator id\": \"") + room.owner_id + QString("\", \"task creator id\": \"") + task.owner_id + QString("\", \"task label\": \"") + task.task_name + QString("\"}");

    QNetworkReply *m_reply = m_networkManager.post(request, jsonProfileCreationBody.toUtf8());
    connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleTaskDeletingResponse);
}

void NetworkManager::handleTaskDeletingResponse() {
    QNetworkReply *m_reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QString response(m_reply->readAll());
    m_reply->deleteLater();
    /* DEBUG */ qInfo() << QString("server response: ") + response;
}

void NetworkManager::sendGettingUserRoomsRequest() {
    QNetworkRequest request(host + "/GetUserRooms");
    request.setRawHeader(QByteArray("Authorization"), this->token);

    QNetworkReply *m_reply = m_networkManager.get(request);
    connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleGettingUserRoomsResponse);
}

void NetworkManager::handleGettingUserRoomsResponse() {
    QNetworkReply *m_reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QString response(m_reply->readAll());
    m_reply->deleteLater();
    /* DEBUG */ qInfo() << QString("server response: ") + response;
}

void NetworkManager::sendGettingUserTasksRequest() {
    QNetworkRequest request(host + "/GetUserTasks");
    request.setRawHeader(QByteArray("Authorization"), this->token);

    QNetworkReply *m_reply = m_networkManager.get(request);
    connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleGettingUserTasksResponse);
}

void NetworkManager::handleGettingUserTasksResponse() {
    QNetworkReply *m_reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QString response(m_reply->readAll());
    m_reply->deleteLater();
    /* DEBUG */ qInfo() << QString("server response: ") + response;
}

void NetworkManager::sendGettingRoomTasksRequest(RoomInfo &room) {
    QNetworkRequest request(host + "/GetRoomTasks");
    request.setRawHeader(QByteArray("Authorization"), this->token);

    QString jsonProfileCreationBody = QString("{\"room label\": \"") + room.room_name + QString("\", \"room creator id\": \"") + room.owner_id + QString("\"}");

    QNetworkReply *m_reply = m_networkManager.get(request, jsonProfileCreationBody.toUtf8());
    connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleGettingUserTasksResponse);
}

void NetworkManager::handleGettingRoomTasksResponse() {
    QNetworkReply *m_reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QString response(m_reply->readAll());
    m_reply->deleteLater();
    /* DEBUG */ qInfo() << QString("server response: ") + response;
}

void NetworkManager::sendGettingRoomUsersRequest(RoomInfo &room) {
    QNetworkRequest request(host + "/GetRoomTasks");
    request.setRawHeader(QByteArray("Authorization"), this->token);

    QString jsonProfileCreationBody = QString("{\"room label\": \"") + room.room_name + QString("\", \"room creator id\": \"") + room.owner_id + QString("\"}");

    QNetworkReply *m_reply = m_networkManager.get(request, jsonProfileCreationBody.toUtf8());
    connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleGettingRoomUsersResponse);
}

void NetworkManager::handleGettingRoomUsersResponse() {
    QNetworkReply *m_reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QString response(m_reply->readAll());
    m_reply->deleteLater();
    /* DEBUG */ qInfo() << QString("server response: ") + response;
}
