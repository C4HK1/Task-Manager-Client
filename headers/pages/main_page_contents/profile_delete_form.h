#ifndef PROFILE_DELETE_FORM_H
#define PROFILE_DELETE_FORM_H

#include "base_page.h"
#include "room_page.h"

class MainPage;

class ProfileDeleteForm : public BasePage {
    Q_OBJECT
public:
    MainPage *mainPage;

    ProfileDeleteForm(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage);
    ~ProfileDeleteForm();
signals:
public slots:
    void closeProfileDeleteForm();
    void profileDelete();
    void finishProfileDelete(ServerStatus serverStatus);
private:
};

#endif // PROFILE_DELETE_FORM_H
