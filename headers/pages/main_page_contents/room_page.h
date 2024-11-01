#ifndef ROOM_PAGE_H
#define ROOM_PAGE_H

#include "base_page.h"

class RoomPage : public BasePage {
    Q_OBJECT
public:
    RoomPage(QQmlEngine *engine, QQuickItem *container, Room room);
    ~RoomPage();
signals:
    void switchToTaskCreation();
public slots:
    void roomPageInitialization(ServerStatus serverStatus, Tasks tasks);
    void handleTaskCreationStatus(ServerStatus serverStatus, Task task);
    void openTaskCreationForm();

private:
    Room room;
    Tasks tasks;
    QQmlComponent *taskComponent;
    QQuickItem *tasksContainer;
};

#endif // ROOM__PAGE_H
