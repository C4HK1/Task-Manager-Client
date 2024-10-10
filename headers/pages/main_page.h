#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include "base_page.h"
#include "rooms_page.h"
#include "content_structures.h"
#include "network_manager.h"

class MainPage : public BasePage {
    Q_OBJECT
public:
    MainPage(QQmlEngine *engine, QQuickItem *container, NetworkManager *net_manager);
    void initializeRooms(QList<RoomInfo*> rooms_info);
    void setCurrentPage(BasePage *page);
    template <typename PageType, typename ...Args> requires (IsPage<PageType> && !IsRoomsPage<PageType>)
    void switchPage(Args...);
    template <typename PageType, typename ...Args> requires IsRoomsPage<PageType>
    void switchPage(Args...);

private:
    QQuickItem *workspace = nullptr;
    BasePage *cur_page = nullptr;
    QList<RoomInfo*> rooms;
    NetworkManager *net_manager;
};

// extern template void MainPage::switchPage<ListRoomsPage>();

#endif // MAIN_PAGE_H
