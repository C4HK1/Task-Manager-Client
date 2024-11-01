#ifndef ROOM_CREATION_PAGE_H
#define ROOM_CREATION_PAGE_H

#include "base_page.h"

class MainPage;

class RoomCreationPage : public BasePage {
    Q_OBJECT
public:
    RoomCreationPage(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage);
    ~RoomCreationPage();

public slots:
    void createRoom(QString roomName, QString description);
    void finishCreateRoom(ServerStatus serverStatus, Room room);

private:
    MainPage *mainPage;
};

#endif // ROOM_CREATION_PAGE_H
