#ifndef PROFILE_DELETE_FORM_H
#define PROFILE_DELETE_FORM_H

#include "base_form.h"
#include "room.h"

class HomePage;

class ProfileDeleteForm : public BaseForm {
    Q_OBJECT
public:
    HomePage *homePage;

    ProfileDeleteForm(QQmlEngine *engine, QQuickItem *container, HomePage *homePage);
    ~ProfileDeleteForm();
signals:
public slots:
    void closeProfileDeleteForm();
    void profileDelete();
    void finishProfileDelete(Models::ServerStatus serverStatus);
protected:
private:
    QQuickItem *container;
};

#endif // PROFILE_DELETE_FORM_H
