#ifndef LIST_ROOMS_PAGE_H
#define LIST_ROOMS_PAGE_H

#include "rooms_page.h"

class ListRoomsPage : public RoomsPage {
    Q_OBJECT
public:
    ListRoomsPage(QQmlEngine *engine, QQuickItem *container);
    void AddRoom(RoomInfo *ri) override;
};

#endif // LIST_ROOMS_PAGE_H
