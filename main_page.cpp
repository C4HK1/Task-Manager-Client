#include "main_page.h"
#include "profile_page.h"
#include "widget_rooms_page.h"
#include "list_rooms_page.h"
#include "settings_page.h"

MainPage::MainPage(QQmlEngine *engine, QQuickItem *container) :
    BasePage(engine, container, "MainWorkspace.qml"), workspace(object->findChild<QQuickItem*>("workspace"))
{
    switchToWidgetRooms();
}

void MainPage::setCurrentPage(BasePage *page) {
    if (cur_page != nullptr) {
        cur_page->deleteLater();
    }

    cur_page = page;
}

void MainPage::switchToWidgetRooms() {
    setCurrentPage(new WidgetRoomsPage(engine, workspace));
}

void MainPage::switchToListRooms() {
    setCurrentPage(new ListRoomsPage(engine, workspace));
}

void MainPage::switchToSettings() {
    setCurrentPage(new SettingsPage(engine, workspace));
}

void MainPage::switchToProfile() {
    setCurrentPage(new ProfilePage(engine, workspace));
}
