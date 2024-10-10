#include "main_page.h"
#include "profile_page.h"
#include "widget_rooms_page.h"
#include "list_rooms_page.h"
#include "settings_page.h"
#include "room_creation_page.h"

MainPage::MainPage(QQmlEngine *engine, QQuickItem *container) :
    BasePage(engine, container, "qml/MainWorkspace.qml"), workspace(object->findChild<QQuickItem*>("workspace"))
{
    rooms.append(new RoomInfo{QString("asdf"), QString("qwerty")});
    rooms.append(new RoomInfo{QString("Hamster Combat"), QString("Pavel Durov")});
    rooms.append(new RoomInfo{QString("zhopa"), QString("hui")});

    switchToWidgetRooms();
}

void MainPage::setCurrentPage(BasePage *page) {
    if (cur_page != nullptr) {
        cur_page->deleteLater();
    }

    cur_page = page;
}

void MainPage::switchToWidgetRooms() {
    WidgetRoomsPage *widget_page;
    setCurrentPage(widget_page = new WidgetRoomsPage(engine, workspace));

    for(auto &r : rooms){
        widget_page->createRoomItem(r);
    }
}

void MainPage::switchToListRooms() {
    ListRoomsPage *list_page;
    setCurrentPage(list_page = new ListRoomsPage(engine, workspace));

    for(auto &r : rooms){
        list_page->createRoomItem(r);
    }
}

void MainPage::switchToSettings() {
    setCurrentPage(new SettingsPage(engine, workspace));
}

void MainPage::switchToProfile() {
    setCurrentPage(new ProfilePage(engine, workspace));
}

void MainPage::switchToRoomCreation() {
    setCurrentPage(new RoomCreationPage(engine, workspace));
}
