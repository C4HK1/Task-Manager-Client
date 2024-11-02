#ifndef PROFILE_PAGE_H
#define PROFILE_PAGE_H

#include "base_page.h"

class MainPage;

class ProfilePage : public BasePage
{
    Q_OBJECT
public:
    MainPage *mainPage;

    explicit ProfilePage(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage);

signals:
};

#endif // PROFILE_PAGE_H
