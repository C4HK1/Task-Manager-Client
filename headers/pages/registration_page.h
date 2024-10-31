#ifndef REGISTRATION_PAGE_H
#define REGISTRATION_PAGE_H

#include "base_page.h"

class RegistrationPage : public BasePage {
    Q_OBJECT
    QML_ELEMENT

    MainApplication *mainApp;
public:
    RegistrationPage(QQmlEngine *engine, QQuickItem *container, MainApplication *mainApp);
public slots:
    void finishCreateProfile(ServerStatus serverStatus, QByteArray jwt);
};

#endif // REGISTRATION_PAGE_H
