#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include "base_element.h"
#include "base_page.h"

class HomePage;

class Settings : public BasePage {
    Q_OBJECT
public:
    HomePage *homePage;

    void update() override;
    void leave() override;
    Settings(QQmlEngine *engine, HomePage *homePage);
    ~Settings();
signals:
public slots:
protected:
private:
};

#endif // SETTINGS_PAGE_H
