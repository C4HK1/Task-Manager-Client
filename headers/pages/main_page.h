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
    void setCurrentForm(BasePage *form);

    template <typename FormType, typename ...Args> requires IsPage<FormType>
    void switchForm(Args... args);

    template <typename PageType, typename ...Args> requires IsPage<PageType>
    void switchPage(Args... args);
signals:
    void switchToLogginingPage();
    void switchToRegistrationPage();
public slots:
    void switchToRoom(Room room);
    void switchToWidgetRooms();
    void switchToListRooms();
    void switchToSettings();
    void switchToRoomCreation();
    void switchToProfile();
    void switchToTasks();

    void switchToTaskCreation();

    void closeForm();

    void deleteProfile();
    void finishDeleteProfile(ServerStatus serverStatus);
    void loggout();
private:
    QQuickItem *workspace = nullptr;
    BasePage *curPage = nullptr;
    BasePage *curForm = nullptr;
    Rooms rooms;
};

// extern template void MainPage::switchPage<ListRoomsPage>();

#endif // MAIN_PAGE_H
