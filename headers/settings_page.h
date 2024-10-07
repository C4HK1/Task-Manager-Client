#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include "base_page.h"

class SettingsPage : public BasePage
{
    Q_OBJECT
public:
    SettingsPage(QQmlEngine *engine, QQuickItem *container);

signals:
};

#endif // SETTINGS_PAGE_H
