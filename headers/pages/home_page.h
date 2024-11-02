#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include <QSignalMapper>
#include "base_element.h"
#include "models.h"
#include "network_manager.h"
#include "home_page_contents.h"
#include "main_application.h"

class HomePage : public BaseElement {
    Q_OBJECT
public:
    MainApplication *mainApp;

    HomePage(QQmlEngine *engine, QQuickItem *container, MainApplication *mainApp);
    ~HomePage();

    void setCurrentPage(BaseElement *page);
    void setCurrentForm(BaseElement *form);

    template <typename FormType, typename ...Args> requires IsElement<FormType>
    void switchForm(Args... args);

    template <typename PageType, typename ...Args> requires IsElement<PageType>
    void switchPage(Args... args);
signals:
public slots:
    void switchToRoom(Models::Room room);
    void switchToWidgetRooms();
    void switchToListRooms();
    void switchToSettings();
    void switchToRoomCreation();
    void switchToProfile();
    void switchToTasks();

    void switchToLoggoutForm();
    void switchToProfileDeleteForm();

    void closeForm();
protected:
private:
    QQuickItem *workspace = nullptr;
    BaseElement *curWorkspaceElement = nullptr;
    BaseElement *curForm = nullptr;
    Models::Rooms rooms;
};

// extern template void homePage::switchPage<ListRoomsPage>();

#endif // HOME_PAGE_H
