#ifndef ROOMS_PAGE_H
#define ROOMS_PAGE_H

#include "base_page.h"
#include "content_structures.h"

class MainPage;

class RoomsPage : public BasePage
{
    Q_OBJECT
public:
    RoomsPage(QQmlEngine *engine, QQuickItem *container, QString moduleName, QString itemName, MainPage *mainPage);
    virtual void createRoomItem(Room &room) = 0;
    ~RoomsPage();

public slots:
    void finishSwitchToRoom(ServerStatus serverStatus, Room room);
    void initializeContents(ServerStatus serverStatus, Rooms rooms);
    void switchToRoom(int roomCreatorID, QString roomName);
    void switchToRoomCreation();

signals:

protected:
    MainPage *mainPage;
    QList<QQuickItem*> roomsItems;
    QQmlComponent *itemComponent;

    Rooms rooms;
};

template <typename T>
concept IsRoomsPage = std::is_base_of<RoomsPage, T>::value;

#endif // SETTINGS_PAGE_H
