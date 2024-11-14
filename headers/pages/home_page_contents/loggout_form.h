#ifndef LOGGOUT_FORM_H
#define LOGGOUT_FORM_H

#include "base_form.h"
#include "room.h"

class HomePage;

class LoggoutForm : public BaseForm {
    Q_OBJECT
public:
    HomePage *homePage;

    LoggoutForm(QQmlEngine *engine, QQuickItem *parent, HomePage *homePage);
    ~LoggoutForm();
signals:
public slots:
    void loggout();
    void closeLoggoutForm();
protected:
private:
};

#endif // LOGGOUT_FORM_H
