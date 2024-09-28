#include "network_manager.h"
#include "main_application.h"

const QString NetworkManager::host("http://localhost:8080");

NetworkManager::NetworkManager(MainApplication *app) : QObject{app}, app(app) {}

void NetworkManager::sendAuthorizationRequest(QString login, QString password)
{
    QNetworkRequest request(host);

    QString jsonAuthInfo = QString("{\"login\": \"") + login + QString("\", \"password\": \"") + password + QString("\"}");

    QNetworkReply *m_reply = m_networkManager.post(request, jsonAuthInfo.toUtf8());
    connect(m_reply, &QNetworkReply::finished, this, &NetworkManager::handleAuthorizationResponse);
    /* DEBUG */ qInfo() << QString("http post requeast was send on " + request.url().toString() + " with data: " + jsonAuthInfo);
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

            sendAuthenticationRequest(token);
        }
    } catch (std::exception &ex) {
        qInfo() << ex.what();
        return;
    }
}

void NetworkManager::sendProfileDeletingRequest()
{
    QFile file("data/authentication_key.organizer");

    file.open(QIODevice::ReadOnly);
    QByteArray token = file.readAll();
    file.close();

    QNetworkRequest request(host + "/ProfileDeleting");
    request.setRawHeader(QByteArray("Authorization"), token);
    QNetworkReply *m_reply = m_networkManager.get(request);
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
