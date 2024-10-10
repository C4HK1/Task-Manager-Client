#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include "base_page.h"

struct TaskInfo {
    QString task_name, owner_name, owner_id;
};

struct RoomInfo {
    QString room_name, owner_name, owner_id;
    QList<TaskInfo*> tasks;

    QQuickItem *room_item = nullptr;

    ~RoomInfo() { if(room_item != nullptr) room_item->deleteLater(); }
};

class MainPage : public BasePage {
    Q_OBJECT
public:
    MainPage(QQmlEngine *engine, QQuickItem *container);
    void setCurrentPage(BasePage *page);
    void switchToSettings();
    void switchToProfile();
    void switchToWidgetRooms();
    void switchToListRooms();
    void switchToRoomCreation();

private:
    QQuickItem *workspace = nullptr;
    BasePage *cur_page = nullptr;
    QList<RoomInfo*> rooms;
};

#endif // MAIN_PAGE_H
