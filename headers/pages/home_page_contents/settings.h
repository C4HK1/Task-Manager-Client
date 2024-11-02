#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include "base_element.h"

class HomePage;

class Settings : public BaseElement {
    Q_OBJECT
public:
    HomePage *homePage;

    Settings(QQmlEngine *engine, QQuickItem *container, HomePage *homePage);
    ~Settings();
signals:
public slots:
protected:
private:
};

#endif // SETTINGS_PAGE_H
