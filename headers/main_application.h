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
#include "base_page.h"

class NetworkManager;

class MainApplication : public QGuiApplication {
    Q_OBJECT
    Q_PROPERTY(bool loginingError MEMBER m_loginingError NOTIFY loginingErrorChanged)
public:
    explicit MainApplication(int argc = 0, char **argv = nullptr);
    virtual ~MainApplication();
    QQuickItem* loadQmlFrame(QString fileName);
    void tryAuthenticate();
    void SetCurrentPage(BasePage *page);
    template <typename T> requires IsPage<T>
    void switchPage();
    Q_INVOKABLE void switchToRegister();
    Q_INVOKABLE void switchToSettings();
    Q_INVOKABLE void switchToProfile();
    Q_INVOKABLE void switchToWidgetRooms();
    Q_INVOKABLE void switchToListRooms();
    Q_INVOKABLE void switchToRoomCreation();

signals:
    void loginingErrorChanged();

public slots:
    void handleAuthentication(bool success);
    void outFromAccount();

private:
    NetworkManager *net_manager;
    QQmlEngine *engine;
    QQuickWindow *main_window = nullptr;
    BasePage *cur_page = nullptr;
    bool m_loginingError = false;
};

#endif // MAIN_APPLICATION_H
