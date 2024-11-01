#ifndef MAIN_APPLICATION_H
#define MAIN_APPLICATION_H

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
#include "content_structures.h"

class NetworkManager;

class MainApplication : public QGuiApplication {
    Q_OBJECT
public:
    explicit MainApplication(int argc = 0, char **argv = nullptr);
    virtual ~MainApplication();

    QQuickItem* loadQmlFrame(QString fileName);

    void tryAuthenticate();

    void SetCurrentPage(BasePage *page);

    template <typename T, typename ...Args> requires IsPage<T>
    void switchPage(Args...);
public slots:
    void handleAuthentication(ServerStatus serverStatus);
    void switchToLogginingPage();
    void switchToRegistrationPage();
    void switchToHomePage();
private:
    NetworkManager *netManager;
    QQmlEngine *engine;
    QQuickWindow *mainWindow = nullptr;
    BasePage *curPage = nullptr;
};

#endif // MAIN_APPLICATION_H
