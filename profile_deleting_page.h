#ifndef PROFILE_DELETING_PAGE_H
#define PROFILE_DELETING_PAGE_H

#include "base_page.h"

class ProfileDeletingPage : public BasePage {
    Q_OBJECT
    QML_ELEMENT
public:
    ProfileDeletingPage(QQmlEngine *engine, BasePage *container);
};

#endif // PROFILE_DELETING_PAGE_H
