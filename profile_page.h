#ifndef PROFILE_PAGE_H
#define PROFILE_PAGE_H

#include "base_page.h"

class ProfilePage : public BasePage
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit ProfilePage(QQmlEngine *engine, QQuickItem *container);

signals:
};

#endif // PROFILE_PAGE_H
