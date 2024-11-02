#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include "base_page.h"

class MainPage;

class SettingsPage : public BasePage {
    Q_OBJECT
public:
    MainPage *mainPage;

    SettingsPage(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage);

signals:
};

#endif // SETTINGS_PAGE_H
