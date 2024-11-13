#ifndef ROOMS_PAGE_H
#define ROOMS_PAGE_H

#include "base_element.h"
#include "models.h"

class HomePage;

class RoomsList : public BaseElement
{
    Q_OBJECT
public:
    HomePage *homePage;

    RoomsList(QQmlEngine *engine, QString moduleName, QString itemName, HomePage *homePage);
    virtual void createRoomItem(Models::Room &room) = 0;
    ~RoomsList();
signals:
public slots:
    void finishSwitchToRoom(Models::ServerStatus serverStatus, Models::Room room);
    void initializeContents(Models::ServerStatus serverStatus, Models::Rooms rooms);
    void switchToRoom(int roomCreatorID, QString roomName);
    void switchToRoomCreation();
signals:
protected:
    QList<QQuickItem*> roomsItems;
    QQmlComponent *itemComponent;

    Models::Rooms rooms;
private:
};

template <typename T>
concept IsRoomsPage = std::is_base_of<RoomsList, T>::value;

#endif // SETTINGS_PAGE_H
