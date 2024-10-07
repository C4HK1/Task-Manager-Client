#ifndef AUTHORIZATION_PAGE_H
#define AUTHORIZATION_PAGE_H

#include "base_page.h"

class AuthorizationPage : public BasePage {
    Q_OBJECT
public:
    AuthorizationPage(QQmlEngine *engine, QQuickItem *container);
};

#endif // AUTHORIZATION_PAGE_H
