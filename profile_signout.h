#ifndef PROFILE_SIGNOUT_H
#define PROFILE_SIGNOUT_H

#include "base_page.h"

class ProfileSignout : public BasePage {
    Q_OBJECT
    QML_ELEMENT
public:
    ProfileSignout(QQmlEngine *engine, BasePage *container);
};

#endif // PROFILE_SIGNOUT_H
