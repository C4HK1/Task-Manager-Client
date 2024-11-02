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

#include "base_element.h"
#include "models.h"

class NetworkManager;

class MainApplication : public QGuiApplication {
    Q_OBJECT
public:
    explicit MainApplication(int argc = 0, char **argv = nullptr);
    virtual ~MainApplication();

    QQuickItem* loadQmlFrame(QString fileName);

    void tryAuthenticate();

    void SetCurrentPage(BaseElement *page);

    template <typename T, typename ...Args> requires IsElement<T>
    void switchPage(Args...);
signals:
public slots:
    void handleAuthentication(Models::ServerStatus serverStatus);
    void switchToLogginingPage();
    void switchToRegistrationPage();
    void switchToHomePage();
protected:
private:
    NetworkManager *netManager;
    QQmlEngine *engine;
    QQuickWindow *mainWindow = nullptr;
    BaseElement *curPage = nullptr;
};

#endif // MAIN_APPLICATION_H
