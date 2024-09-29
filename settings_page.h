#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include "base_page.h"

class SettingsPage : public BasePage
{
    Q_OBJECT
    QML_ELEMENT
public:
    SettingsPage(QQmlEngine *engine, QQuickItem *container);

signals:
};

#endif // SETTINGS_PAGE_H
