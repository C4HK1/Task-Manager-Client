#ifndef ROOMS_PAGE_H
#define ROOMS_PAGE_H

#include "base_page.h"

struct TaskInfo {
    QString task_name, owner_name, owner_id;
};

struct RoomInfo {
    QString room_name, owner_name, owner_id;

    QList<TaskInfo*> tasks;
};

class RoomsPage : public BasePage
{
    Q_OBJECT
public:
    RoomsPage(QQmlEngine *engine, QQuickItem *container, QString moduleName, QString itemName);
    virtual void AddRoom(RoomInfo *ri) = 0;
    ~RoomsPage();

signals:

private:
    QList<RoomInfo*> rooms;
    QQmlComponent *item_component;
};

#endif // SETTINGS_PAGE_H
