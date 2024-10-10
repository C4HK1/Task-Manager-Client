#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include "base_page.h"
#include "rooms_page.h"
#include "content_structures.h"

class MainPage : public BasePage {
    Q_OBJECT
public:
    MainPage(QQmlEngine *engine, QQuickItem *container);
    void setCurrentPage(BasePage *page);
    template <typename PageType> requires (IsPage<PageType> && !IsRoomsPage<PageType>)
    void switchPage();
    template <typename PageType> requires IsRoomsPage<PageType>
    void switchPage();

private:
    QQuickItem *workspace = nullptr;
    BasePage *cur_page = nullptr;
    QList<RoomInfo*> rooms;
};

// extern template void MainPage::switchPage<ListRoomsPage>();

#endif // MAIN_PAGE_H
