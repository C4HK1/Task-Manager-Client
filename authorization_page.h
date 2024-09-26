#ifndef AUTHORIZATION_PAGE_H
#define AUTHORIZATION_PAGE_H

#include "base_page.h"

class AuthorizationPage : public BasePage {
    Q_OBJECT
public:
    AuthorizationPage(MainApplication *app);
    static void loadPage(MainApplication *app);
};

#endif // AUTHORIZATION_PAGE_H
