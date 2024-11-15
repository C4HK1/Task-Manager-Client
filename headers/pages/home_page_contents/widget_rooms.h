#ifndef WIDGET_ROOMS_PAGE_H
#define WIDGET_ROOMS_PAGE_H

#include "rooms_list.h"

class HomePage;

class WidgetRooms : public RoomsList {
    Q_OBJECT
public:
    WidgetRooms(QQmlEngine *engine, HomePage *homePage);
    ~WidgetRooms();
signals:
public slots:
protected:
private:
};

#endif // WIDGET_ROOMS_PAGE_H
