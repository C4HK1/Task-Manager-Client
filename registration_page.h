#ifndef REGISTRATION_PAGE_H
#define REGISTRATION_PAGE_H

#include "base_page.h"

class RegistrationPage : public BasePage {
    Q_OBJECT
    QML_ELEMENT
public:
    RegistrationPage(MainApplication *app);
    static void loadPage(MainApplication *app);
};

#endif // REGISTRATION_PAGE_H
