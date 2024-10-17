#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include <QSignalMapper>
#include "base_page.h"
#include "rooms_page.h"
#include "tasks_page.h"
#include "content_structures.h"
#include "network_manager.h"
#include "main_page_contents.h"

class MainPage : public BasePage {
    Q_OBJECT
public:
    MainPage(QQmlEngine *engine, QQuickItem *container);
    void initializeContents(QList<RoomInfo*> rooms_info);
    void initializeRoomTasks(QList<TaskInfo*> tasks_info);
    void setCurrentPage(BasePage *page);
    template <typename PageType, typename ...Args> requires (IsPage<PageType> && !IsRoomsPage<PageType> && !IsTasksPage<PageType>)
    void switchPage(Args...);
    template <typename PageType, typename ...Args> requires IsRoomsPage<PageType>
    void switchPage(Args...);
    template <typename PageType, typename ...Args> requires IsTasksPage<PageType>
    void switchPage(Args...);

public slots:
    void switchToRoom(RoomInfo *ri);
    void openRoom(QString id);
    void switchToWidgetRooms();
    void switchToListRooms();
    void switchToSettings();
    void switchToRoomCreation();
    void switchToProfile();
    void switchToTasks();

private:
    QQuickItem *workspace = nullptr;
    BasePage *cur_page = nullptr;
    QList<RoomInfo*> rooms;
    QList<TaskInfo*> tasks;
};

// extern template void MainPage::switchPage<ListRoomsPage>();

#endif // MAIN_PAGE_H
