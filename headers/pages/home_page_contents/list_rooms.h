#ifndef LIST_ROOMS_PAGE_H
#define LIST_ROOMS_PAGE_H

#include "rooms_list.h"

class HomePage;

class ListRooms : public RoomsList {
    Q_OBJECT
public:
    ListRooms(QQmlEngine *engine, HomePage *homePage);
    ~ListRooms();

    void createRoomItem(Models::Room &room) override;
signals:
public slots:
protected:
private:
    QQuickItem *listContainer;
};

#endif // LIST_ROOMS_PAGE_H
