#ifndef AUTHORIZATION_PAGE_H
#define AUTHORIZATION_PAGE_H

#include "base_page.h"

class LogginingPage : public BasePage {
    Q_OBJECT
public:
    LogginingPage(QQmlEngine *engine, QQuickItem *container);
signals:
    void switchToRegistrationPage();
    void switchToHomePage();
public slots:
    void finishLoggining(ServerStatus serverStatus, QByteArray jwt);
    void switchToRegistration();
    void loggin(QString login, QString password);
};

#endif // AUTHORIZATION_PAGE_H
