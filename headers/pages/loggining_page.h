#ifndef AUTHORIZATION_PAGE_H
#define AUTHORIZATION_PAGE_H

#include "base_page.h"

class LogginingPage : public BasePage {
    Q_OBJECT

    MainApplication *mainApp;
public:
    LogginingPage(QQmlEngine *engine, QQuickItem *container, MainApplication *mainApp);
public slots:
    void finishLoggining(ServerStatus serverStatus, QByteArray jwt);
};

#endif // AUTHORIZATION_PAGE_H
