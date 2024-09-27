#ifndef REGISTRATION_PAGE_H
#define REGISTRATION_PAGE_H

#include "base_page.h"

class RegistrationPage : public BasePage {
    Q_OBJECT
    QML_ELEMENT
public:
    RegistrationPage(QQmlEngine *engine, QQuickItem *container);
};

#endif // REGISTRATION_PAGE_H
