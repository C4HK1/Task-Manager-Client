#ifndef ROOM_CREATION_PAGE_H
#define ROOM_CREATION_PAGE_H

#include "base_element.h"
#include "base_page.h"

class HomePage;

class RoomCreation : public BasePage {
    Q_OBJECT
public:
    HomePage *homePage;

    RoomCreation(QQmlEngine *engine, HomePage *homePage);
    void update() override;
    void leave() override;
    ~RoomCreation();
signals:
public slots:
    void createRoom(QString roomName, QString description);
    void finishCreateRoom(Models::ServerStatus serverStatus, Models::Room room);
protected:
private:
};

#endif // ROOM_CREATION_PAGE_H
