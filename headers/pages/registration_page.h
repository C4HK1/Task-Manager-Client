#ifndef REGISTRATION_PAGE_H
#define REGISTRATION_PAGE_H

#include "base_page.h"

class MainApplication;

class RegistrationPage : public BasePage {
    Q_OBJECT
    QML_ELEMENT
public:
    MainApplication *mainApp;

    RegistrationPage(QQmlEngine *engine, QQuickItem *container, MainApplication *mainApp);
public slots:
    void createProfile(QString name, QString login, QString password, QString email, QString phone);
    void finishCreateProfile(ServerStatus serverStatus, QByteArray jwt);
};

#endif // REGISTRATION_PAGE_H
