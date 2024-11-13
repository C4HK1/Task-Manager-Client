#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include <QSignalMapper>
#include "base_element.h"
#include "models.h"
#include "network_manager.h"
#include "home_page_contents.h"
#include "main_application.h"
#include "navigation_service.h"

class HomePage : public BaseElement {
    Q_OBJECT
public:
    MainApplication *mainApp;

    HomePage(QQmlEngine *engine, MainApplication *mainApp);
    ~HomePage();

    void setCurrentForm(BaseElement *form);

    template <typename FormType, typename ...Args> requires IsElement<FormType>
    void switchForm(Args... args);

    template <typename ElementType, typename ...Args> requires IsElement<ElementType>
    BaseElement* createElement(Args... args);

signals:
public slots:
    void switchToRoom(Models::Room room);
    void switchToWidgetRooms();
    void switchToListRooms();
    void switchToSettings();
    void switchToRoomCreation();
    void switchToProfile();

    void switchToLoggoutForm();
    void switchToProfileDeleteForm();

    void switchToAllTasks();
    void switchToReviewedTasks();
    void switchToAssignedTasks();

    void switchToAllInvites();
    void switchToReceivedInvites();
    void switchToSendedInvites();

    void closeForm();
    void closePage();
protected:
private:
    QQuickItem *workspace = nullptr;
    NavigationService *nav_service = nullptr;
    BaseElement *curForm = nullptr;
    Models::Rooms rooms;
};

// extern template void homePage::switchPage<ListRoomsPage>();

#endif // HOME_PAGE_H
