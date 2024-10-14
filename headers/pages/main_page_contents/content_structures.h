#ifndef CONTENT_STRUCTURES_H
#define CONTENT_STRUCTURES_H

#include <QQuickItem>

struct RoomInfo;

struct TaskInfo {
    QString task_name, owner_name, owner_id, room_id;
    RoomInfo *parent;

    QQuickItem *task_item;

    ~TaskInfo() { if(task_item != nullptr) task_item->deleteLater(); }
};

struct RoomInfo {
    QString room_name, owner_name, owner_id;
    QList<TaskInfo*> tasks;

    QQuickItem *room_item = nullptr;

    ~RoomInfo() { if(room_item != nullptr) room_item->deleteLater(); }
};

#endif // CONTENT_STRUCTURES_H
