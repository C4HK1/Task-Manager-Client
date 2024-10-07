#ifndef WIDGET_ROOMS_PAGE_H
#define WIDGET_ROOMS_PAGE_H

#include "rooms_page.h"

class WidgetRoomsPage : public RoomsPage {
    Q_OBJECT
public:
    WidgetRoomsPage(QQmlEngine *engine, QQuickItem *container);
    void AddRoom(RoomInfo *ri) override;
};

#endif // WIDGET_ROOMS_PAGE_H
