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

    connect(net_manager, &NetworkManager::gotRooms, this, &MainPage::initializeContents);
    connect(net_manager, &NetworkManager::gotRoom, this, &MainPage::switchToRoom);
    net_manager->sendGettingUserRoomsRequest();
}

void MainPage::initializeContents(QList<RoomInfo*> rooms_info) {
    for (auto &ri : rooms_info) {
        rooms.append(ri);

        for(auto &ti : ri->tasks) {
            tasks.append(ti);
        }
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

    connect(page->getObject(), SIGNAL(switchToRoomCreation()), this, SLOT(switchToRoomCreation()));

    for(auto &r : rooms){
        page->createRoomItem(r);
    }
}

template <typename PageType, typename ...Args> requires IsTasksPage<PageType>
void MainPage::switchPage(Args... args) {
    TasksPage *page;
    setCurrentPage(page = new PageType(engine, workspace, args...));

    for(auto &t : tasks){
        page->createTaskItem(t);
        connect(t->task_item, SIGNAL(openRoom(QString)), this, SLOT(openRoom(QString)));
    }

    page->sortBy("task_name", true);
}

template <typename PageType, typename ...Args> requires (IsPage<PageType> && !IsRoomsPage<PageType> && !IsTasksPage<PageType>)
void MainPage::switchPage(Args... args) {
    setCurrentPage(new PageType(engine, workspace, args...));
}

void MainPage::switchToRoom(RoomInfo *ri) {
    switchPage<RoomPage>(ri);
}

void MainPage::openRoom(QString id) {
    for (auto &ti : tasks) {    // REIMPLEMENTATION REQUIRED
        if (ti->room_id == id) {
            switchPage<RoomPage>(ti->parent);
            break;
        }
    }
}

void MainPage::switchToWidgetRooms() { switchPage<WidgetRoomsPage>(); }
void MainPage::switchToListRooms() { switchPage<ListRoomsPage>(); }
void MainPage::switchToSettings() { switchPage<SettingsPage>(); }
void MainPage::switchToRoomCreation() { switchPage<RoomCreationPage>(); }
void MainPage::switchToProfile() { switchPage<ProfilePage>(); }
void MainPage::switchToTasks() { switchPage<TasksPage>(); }
