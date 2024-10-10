#include "main_page.h"
#include "main_page_contents.h"

MainPage::MainPage(QQmlEngine *engine, QQuickItem *container, NetworkManager *net_manager) :
    BasePage(engine, container, "qml/MainWorkspace.qml"),
    workspace(object->findChild<QQuickItem*>("workspace")),
    net_manager(net_manager)
{
    connect(net_manager, &NetworkManager::gotRooms, this, &MainPage::initializeRooms);

    net_manager->sendGettingUserRoomsRequest();
}

void MainPage::initializeRooms(QList<RoomInfo*> rooms_info) {
    for (auto &ri : rooms_info) {
        rooms.append(ri);
    }

    switchPage<WidgetRoomsPage>();
}

void MainPage::setCurrentPage(BasePage *page){
    if (cur_page != nullptr) {
        cur_page->deleteLater();
    }

    cur_page = page;
}

template <typename PageType, typename ...Args> requires IsRoomsPage<PageType>
void MainPage::switchPage(Args... args) {
    RoomsPage *page;
    setCurrentPage(page = new PageType(engine, workspace, args...));

    for(auto &r : rooms){
        page->createRoomItem(r);
    }
}

template <typename PageType, typename ...Args> requires (IsPage<PageType> && !IsRoomsPage<PageType>)
void MainPage::switchPage(Args... args) {
    setCurrentPage(new PageType(engine, workspace, args...));
}

template void MainPage::switchPage<ListRoomsPage>();
template void MainPage::switchPage<SettingsPage>();
template void MainPage::switchPage<RoomCreationPage>();
template void MainPage::switchPage<ProfilePage>();
