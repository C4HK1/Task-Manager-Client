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

class MainApplication;

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(MainApplication *app = nullptr);

    QNetworkRequest* createRequest(QString domain, QString header, QByteArray &data);
    Q_INVOKABLE void sendAuthorizationRequest(QString login, QString password);
    Q_INVOKABLE void sendProfileCreationRequest(QString login, QString password);
    Q_INVOKABLE void sendProfileDeletingRequest();
    void sendAuthenticationRequest(QByteArray token);

signals:
    void authorizationResponseAccept(bool success);

public slots:
    void handleAuthorizationResponse();
    void handleProfileCreationResponse();
    void handleAuthenticationResponse();

private:
    std::function<void(bool)> authenticationHandler;
    QNetworkAccessManager m_networkManager;
    MainApplication *app;
    QList<QNetworkReply*> m_replyList;
    static const QString host;
};

#endif // NETWORK_MANAGER_H
