#ifndef ROOM_PAGE_H
#define ROOM_PAGE_H

#include "base_page.h"
#include "network_manager.h"

class RoomPage : public BasePage {
    Q_OBJECT
public:
    RoomPage(QQmlEngine *engine, QQuickItem *container, RoomInfo *room, NetworkManager *net_manager);
    ~RoomPage();
public slots:
    void loadTasks(QList<TaskInfo *> task);
    void loadTask(bool status);
private:
    NetworkManager *net_manager;
    RoomInfo *room;
    QQmlComponent *task_component;
    QQuickItem *tasks_container;
};

#endif // ROOM__PAGE_H
