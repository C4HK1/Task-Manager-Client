#include "main_page.h"

MainPage::MainPage(QQmlEngine *engine, QQuickItem *container) :
    BasePage(engine, container, "qml/MainWorkspace.qml"),
    workspace(object->findChild<QQuickItem*>("workspace"))
{
    static QList<std::string> switch_slots {
        "switchToWidgetRooms()", "switchToListRooms()", "switchToSettings()",
        "switchToProfile()", "switchToTasks()"
    };

    for (std::string &ss: switch_slots) {
        connect(object, ("2" + ss).c_str(), this, ("1" + ss).c_str());
    }

    switchToWidgetRooms();
}

void MainPage::setCurrentPage(BasePage *page){
    if (curPage != nullptr) {
        curPage->deleteLater();
    }

    curPage = page;
}

template <typename PageType, typename ...Args> requires IsPage<PageType>
void MainPage::switchPage(Args... args) {
    setCurrentPage(new PageType(engine, workspace, args...));
}

void MainPage::switchToRoom(Room room) { switchPage<RoomPage>(room); }
void MainPage::switchToWidgetRooms() { switchPage<WidgetRoomsPage>(this); }
void MainPage::switchToListRooms() { switchPage<ListRoomsPage>(this); }
void MainPage::switchToSettings() { switchPage<SettingsPage>(); }
void MainPage::switchToRoomCreation() { switchPage<RoomCreationPage>(this); }
void MainPage::switchToProfile() { switchPage<ProfilePage>(); }
void MainPage::switchToTasks() { switchPage<TasksPage>(this); }
