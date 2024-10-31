#ifndef WIDGET_ROOMS_PAGE_H
#define WIDGET_ROOMS_PAGE_H

#include "rooms_page.h"

class MainPage;

class WidgetRoomsPage : public RoomsPage {
    Q_OBJECT
public:
    WidgetRoomsPage(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage);
    void createRoomItem(Room &room) override;

private:
    QQuickItem *widgetContainer;
};

#endif // WIDGET_ROOMS_PAGE_H
