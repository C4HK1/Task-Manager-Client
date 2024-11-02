#ifndef PROFILE_PAGE_H
#define PROFILE_PAGE_H

#include "base_element.h"

class HomePage;

class Profile : public BaseElement
{
    Q_OBJECT
public:
    HomePage *homePage;

    explicit Profile(QQmlEngine *engine, QQuickItem *container, HomePage *homePage);
    ~Profile();
signals:
public slots:
protected:
private:
};

#endif // PROFILE_PAGE_H
