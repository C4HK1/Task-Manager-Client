#include "main_page.h"
#include "main_page_contents.h"

MainPage::MainPage(QQmlEngine *engine, QQuickItem *container) :
    BasePage(engine, container, "qml/MainWorkspace.qml"), workspace(object->findChild<QQuickItem*>("workspace"))
{
    rooms.append(new RoomInfo{QString("asdf"), QString("qwerty")});
    rooms.append(new RoomInfo{QString("Hamster Combat"), QString("Pavel Durov")});
    rooms.append(new RoomInfo{QString("zhopa"), QString("hui")});

    switchPage<WidgetRoomsPage>();
}

void MainPage::setCurrentPage(BasePage *page){
    if (cur_page != nullptr) {
        cur_page->deleteLater();
    }

    cur_page = page;
}

template <typename PageType> requires IsRoomsPage<PageType>
void MainPage::switchPage() {
    RoomsPage *page;
    setCurrentPage(page = new PageType(engine, workspace));

    for(auto &r : rooms){
        page->createRoomItem(r);
    }
}

template <typename PageType> requires (IsPage<PageType> && !IsRoomsPage<PageType>)
void MainPage::switchPage() {
    setCurrentPage(new PageType(engine, workspace));
}

template void MainPage::switchPage<ListRoomsPage>();
template void MainPage::switchPage<SettingsPage>();
template void MainPage::switchPage<RoomCreationPage>();
template void MainPage::switchPage<ProfilePage>();
