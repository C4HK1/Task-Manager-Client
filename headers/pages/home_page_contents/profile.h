#ifndef PROFILE_PAGE_H
#define PROFILE_PAGE_H

#include "base_element.h"
#include "base_page.h"

class HomePage;

class Profile : public BasePage
{
    Q_OBJECT
public:
    HomePage *homePage;

    explicit Profile(QQmlEngine *engine, HomePage *homePage);
    void update() override;
    void leave() override;
    ~Profile();
signals:
public slots:
protected:
private:
};

#endif // PROFILE_PAGE_H
