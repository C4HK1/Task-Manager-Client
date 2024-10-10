#ifndef ROOMS_PAGE_H
#define ROOMS_PAGE_H

#include "base_page.h"
#include "main_page.h"

class RoomsPage : public BasePage
{
    Q_OBJECT
public:
    RoomsPage(QQmlEngine *engine, QQuickItem *container, QString moduleName, QString itemName);
    virtual void createRoomItem(RoomInfo *ri) = 0;
    ~RoomsPage();

signals:

protected:
    QList<QQuickItem*> rooms_items;
    QQmlComponent *item_component;
};

#endif // SETTINGS_PAGE_H
