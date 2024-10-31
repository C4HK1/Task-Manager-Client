#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include <QSignalMapper>
#include "base_page.h"
#include "rooms_page.h"
#include "content_structures.h"
#include "network_manager.h"
#include "main_page_contents.h"

class MainPage : public BasePage {
    Q_OBJECT
public:
    MainPage(QQmlEngine *engine, QQuickItem *container);
    void setCurrentPage(BasePage *page);
    template <typename PageType, typename ...Args> requires IsPage<PageType>
    void switchPage(Args... args);
public slots:
    void switchToRoom(Room room);
    void switchToWidgetRooms();
    void switchToListRooms();
    void switchToSettings();
    void switchToRoomCreation();
    void switchToProfile();
    void switchToTasks();

private:
    QQuickItem *workspace = nullptr;
    BasePage *curPage = nullptr;
    Rooms rooms;
};

// extern template void MainPage::switchPage<ListRoomsPage>();

#endif // MAIN_PAGE_H
