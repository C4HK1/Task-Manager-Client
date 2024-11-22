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
#include "base_page.h"
#include "models.h"
#include "navigation_service.h"
#include "kafka/consumer.h"

class NetworkManager;

class MainApplication : public QGuiApplication {
    Q_OBJECT
public:
    explicit MainApplication(int argc = 0, char **argv = nullptr);
    virtual ~MainApplication();

    QQuickItem* loadQmlFrame(QString fileName);

    void tryAuthenticate();
    template <typename ElementType, typename ...Args> requires IsPage<ElementType>
    BasePage* createElement(Args... args);
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
    NavigationService *nav_service = nullptr;
    Kafka::Consumer *consumer;
};

#endif // MAIN_APPLICATION_H
