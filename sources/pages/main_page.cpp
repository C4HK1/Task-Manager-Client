#include "main_page.h"
#include "main_page_contents.h"

MainPage::MainPage(QQmlEngine *engine, QQuickItem *container, NetworkManager *net_manager) :
    BasePage(engine, container, "qml/MainWorkspace.qml"),
    workspace(object->findChild<QQuickItem*>("workspace")),
    net_manager(net_manager)
{
    connect(net_manager, &NetworkManager::gotRooms, this, &MainPage::initializeContents);

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
        connect(t->task_item, SIGNAL(openRoom(QString)), this, SLOT(switchToRoom(QString)));
    }

    page->sortBy();
}

template <typename PageType, typename ...Args> requires (IsPage<PageType> && !IsRoomsPage<PageType> && !IsTasksPage<PageType>)
void MainPage::switchPage(Args... args) {
    setCurrentPage(new PageType(engine, workspace, args...));
}

void MainPage::switchToRoom(QString id) {
    for (auto &ti : tasks) {    // REIMPLEMENTATION REQUIRED
        if (ti->room_id == id) {
            switchPage<RoomPage>(ti->parent, net_manager);
            break;
        }
    }
}

template void MainPage::switchPage<ListRoomsPage>();
template void MainPage::switchPage<SettingsPage>();
template void MainPage::switchPage<RoomCreationPage>(NetworkManager *);
template void MainPage::switchPage<RoomPage>(RoomInfo *, NetworkManager *);
template void MainPage::switchPage<ProfilePage>();
template void MainPage::switchPage<TasksPage>();
