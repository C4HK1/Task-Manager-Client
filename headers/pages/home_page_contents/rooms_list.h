#ifndef ROOMS_PAGE_H
#define ROOMS_PAGE_H

#include "base_element.h"
#include "base_page.h"
#include "models.h"

class HomePage;

class RoomsList : public BasePage
{
    Q_OBJECT
public:
    HomePage *homePage;

    RoomsList(QQmlEngine *engine, QString moduleName, QString itemName, HomePage *homePage);
    void createRoomItem(Models::Room &room);
    void update() override;
    void leave() override;
    void clearContents();
    ~RoomsList();
signals:
public slots:
    void finishSwitchToRoom(Models::ServerStatus serverStatus, Models::Room room);
    void initializeContents(Models::ServerStatus serverStatus, Models::Rooms rooms);
    void sortBy(QString by, bool ascending = true);
    void switchToRoom(int roomCreatorID, QString roomName);
    void switchToRoomCreation();
signals:
protected:
    QQmlComponent *itemComponent;

    QQuickItem *roomContainer;
    Models::Rooms rooms;
    QHash<u_int64_t, QQuickItem*> roomsItems;
private:
};

template <typename T>
concept IsRoomsPage = std::is_base_of<RoomsList, T>::value;

#endif // SETTINGS_PAGE_H
