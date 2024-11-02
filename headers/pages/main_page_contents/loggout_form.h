#ifndef LOGGOUT_FORM_H
#define LOGGOUT_FORM_H

#include "base_page.h"
#include "room_page.h"

class MainPage;

class LoggoutForm : public BasePage {
    Q_OBJECT
public:
    MainPage *mainPage;

    LoggoutForm(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage);
    ~LoggoutForm();
public slots:
    void loggout();
    void closeLoggoutForm();
private:
};

#endif // LOGGOUT_FORM_H
