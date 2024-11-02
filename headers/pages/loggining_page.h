#ifndef AUTHORIZATION_PAGE_H
#define AUTHORIZATION_PAGE_H

#include "base_page.h"
#include "main_application.h"

class MainApplication;

class LogginingPage : public BasePage {
    Q_OBJECT
public:
    MainApplication *mainApp;

    LogginingPage(QQmlEngine *engine, QQuickItem *container, MainApplication *mainApp);
signals:
public slots:
    void finishLoggining(ServerStatus serverStatus, QByteArray jwt);
    void switchToRegistration();
    void loggin(QString login, QString password);
};

#endif // AUTHORIZATION_PAGE_H
