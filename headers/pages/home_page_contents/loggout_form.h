#ifndef LOGGOUT_FORM_H
#define LOGGOUT_FORM_H

#include "base_element.h"
#include "room.h"

class HomePage;

class LoggoutForm : public BaseElement {
    Q_OBJECT
public:
    HomePage *homePage;

    LoggoutForm(QQmlEngine *engine, QQuickItem *container, HomePage *homePage);
    ~LoggoutForm();
signals:
public slots:
    void loggout();
    void closeLoggoutForm();
protected:
private:
    QQuickItem *container;
};

#endif // LOGGOUT_FORM_H
