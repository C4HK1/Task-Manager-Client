#ifndef MAIN_APPLICATION_H
#define MAIN_APPLICATION_H

#pragma once
#include <nlohmann/json.hpp>
#include <QDir>
#include <QFile>
#include <QGuiApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickWindow>

class NetworkManager;

class MainApplication : public QGuiApplication {
    Q_OBJECT
    Q_PROPERTY(bool loginingError MEMBER m_loginingError)
public:
    explicit MainApplication(int argc = 0, char **argv = nullptr);
    virtual ~MainApplication();
    Q_INVOKABLE void loadPage(QString moduleName);
    void tryAuthenticate();

signals:

public slots:
    void handleAuthentication(bool success);

private:
    NetworkManager *net_manager;
    QQmlEngine *engine;
    QQuickWindow *main_window = nullptr;
    QQuickItem *cur_page = nullptr;
    bool m_loginingError = false;
};

#endif // MAIN_APPLICATION_H
