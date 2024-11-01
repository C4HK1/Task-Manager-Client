#ifndef REGISTRATION_PAGE_H
#define REGISTRATION_PAGE_H

#include "base_page.h"

class RegistrationPage : public BasePage {
    Q_OBJECT
    QML_ELEMENT
public:
    RegistrationPage(QQmlEngine *engine, QQuickItem *container);
signals:
    void switchToLogginingPage();
    void switchToHomePage();
public slots:
    void createProfile(QString name, QString login, QString password, QString email, QString phone);
    void finishCreateProfile(ServerStatus serverStatus, QByteArray jwt);
};

#endif // REGISTRATION_PAGE_H
