#ifndef AUTHORIZATION_PAGE_H
#define AUTHORIZATION_PAGE_H

#include "base_element.h"
#include "base_page.h"
#include "main_application.h"

class MainApplication;

class LogginingPage : public BasePage {
    Q_OBJECT
public:
    MainApplication *mainApp;

    LogginingPage(QQmlEngine *engine, MainApplication *mainApp);
    void update() override;
    ~LogginingPage();
signals:
public slots:
    void loggin(QString login, QString password);
    void finishLoggining(Models::ServerStatus serverStatus, QByteArray jwt);

    void switchToRegistration();
protected:
private:
};

#endif // AUTHORIZATION_PAGE_H
