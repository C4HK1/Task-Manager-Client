#ifndef CONTENT_STRUCTURES_H
#define CONTENT_STRUCTURES_H

#include <QQuickItem>

struct TaskInfo {
    QString task_name, owner_name, owner_id;
};

struct RoomInfo {
    QString room_name, owner_name, owner_id;
    QList<TaskInfo*> tasks;

    QQuickItem *room_item = nullptr;

    ~RoomInfo() { if(room_item != nullptr) room_item->deleteLater(); }
};

#endif // CONTENT_STRUCTURES_H
