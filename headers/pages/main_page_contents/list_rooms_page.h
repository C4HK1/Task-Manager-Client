#ifndef LIST_ROOMS_PAGE_H
#define LIST_ROOMS_PAGE_H

#include "rooms_page.h"

class MainPage;

class ListRoomsPage : public RoomsPage {
    Q_OBJECT
public:
    MainPage *mainPage;

    ListRoomsPage(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage);
    void createRoomItem(Room &room) override;

private:
    QQuickItem *listContainer;
};

#endif // LIST_ROOMS_PAGE_H
