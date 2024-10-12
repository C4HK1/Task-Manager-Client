#ifndef ROOM_CREATION_PAGE_H
#define ROOM_CREATION_PAGE_H

#include "base_page.h"
#include "network_manager.h"

class RoomCreationPage : public BasePage {
    Q_OBJECT
public:
    RoomCreationPage(QQmlEngine *engine, QQuickItem *container, NetworkManager *net_manager);
    ~RoomCreationPage();
public slots:
    void loadFailInfo();
private:
    NetworkManager *net_manager;
};

#endif // ROOM_CREATION_PAGE_H
