#ifndef CONTENT_STRUCTURES_H
#define CONTENT_STRUCTURES_H

#include <QQuickItem>

struct TaskInfo;

struct RoomInfo {
    Q_GADGET
public:
    QString room_name, owner_name, owner_id;
    QList<TaskInfo*> tasks;

    QQuickItem *room_item = nullptr;

    ~RoomInfo() { if(room_item != nullptr) room_item->deleteLater(); }

    QVariant property(const char *name) const{
        int index = staticMetaObject.indexOfProperty(name);
        if(index == -1){
            return QVariant();
        }

        return staticMetaObject.property(index).readOnGadget(this);
    }
};

struct TaskInfo {
    Q_GADGET
    Q_PROPERTY(QString task_name MEMBER task_name)
    Q_PROPERTY(QString room_name READ getRoomName)
public:
    QString task_name, owner_name, owner_id, room_id;
    RoomInfo *parent;

    QQuickItem *task_item;

    QString getRoomName() const { return parent->room_name; }

    ~TaskInfo() { if(task_item != nullptr) task_item->deleteLater(); }

    QVariant property(const char *name) const{
        int index = staticMetaObject.indexOfProperty(name);
        if(index == -1){
            return QVariant();
        }

        return staticMetaObject.property(index).readOnGadget(this);
    }
};

#endif // CONTENT_STRUCTURES_H
