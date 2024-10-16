#ifndef CONTENT_STRUCTURES_H
#define CONTENT_STRUCTURES_H

#include <QQuickItem>

struct RoomInfo;

struct TaskInfo {
    Q_GADGET
    Q_PROPERTY(QString task_name MEMBER task_name)
public:
    QString task_name, owner_name, owner_id, room_id;
    RoomInfo *parent;

    QQuickItem *task_item = nullptr;

    ~TaskInfo() { if(task_item != nullptr) task_item->deleteLater(); }
};

struct RoomInfo {
    Q_GADGET
public:
    QString room_name, owner_name, owner_id;
    QList<TaskInfo*> tasks;

    QQuickItem *room_item = nullptr;

    ~RoomInfo() { if(room_item != nullptr) room_item->deleteLater(); }
};

#endif // CONTENT_STRUCTURES_H
