#ifndef REGISTRATION_PAGE_H
#define REGISTRATION_PAGE_H

#include "base_element.h"
#include "base_page.h"

class MainApplication;

class RegistrationPage : public BasePage {
    Q_OBJECT
    QML_ELEMENT
public:
    MainApplication *mainApp;

    RegistrationPage(QQmlEngine *engine, MainApplication *mainApp);
    void update() override;
    void leave() override;
    ~RegistrationPage();
signals:
public slots:
    void createProfile(QString name, QString login, QString password, QString email, QString phone);
    void finishCreateProfile(Models::ServerStatus serverStatus, QByteArray jwt);
protected:
private:
};

#endif // REGISTRATION_PAGE_H
