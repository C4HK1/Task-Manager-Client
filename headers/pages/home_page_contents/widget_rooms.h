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
    void createRoomItem(Models::Room &room) override;
protected:
private:
    QQuickItem *widgetContainer;
};

#endif // WIDGET_ROOMS_PAGE_H
