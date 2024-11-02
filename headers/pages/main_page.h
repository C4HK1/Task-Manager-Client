#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include <QSignalMapper>
#include "base_page.h"
#include "content_structures.h"
#include "network_manager.h"
#include "main_page_contents.h"
#include "main_application.h"

class MainPage : public BasePage {
    Q_OBJECT
public:
    MainApplication *mainApp;

    MainPage(QQmlEngine *engine, QQuickItem *container, MainApplication *mainApp);

    void setCurrentPage(BasePage *page);
    void setCurrentForm(BasePage *form);

    template <typename FormType, typename ...Args> requires IsPage<FormType>
    void switchForm(Args... args);

    template <typename PageType, typename ...Args> requires IsPage<PageType>
    void switchPage(Args... args);
public slots:
    void switchToRoomPage(Room room);
    void switchToWidgetRoomsPage();
    void switchToListRoomsPage();
    void switchToSettingsPage();
    void switchToRoomCreationPage();
    void switchToProfilePage();
    void switchToTasksPage();

    void switchToLoggoutForm();
    void switchToProfileDeleteForm();

    void closeForm();
private:
    QQuickItem *workspace = nullptr;
    BasePage *curPage = nullptr;
    BasePage *curForm = nullptr;
    Rooms rooms;
};

// extern template void MainPage::switchPage<ListRoomsPage>();

#endif // MAIN_PAGE_H
