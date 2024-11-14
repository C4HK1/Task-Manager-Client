#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include <QSignalMapper>
#include "base_page.h"
#include "base_form.h"
#include "models.h"
#include "network_manager.h"
#include "home_page_contents.h"
#include "main_application.h"
#include "navigation_service.h"

class HomePage : public BasePage {
    Q_OBJECT
public:
    MainApplication *mainApp;

    HomePage(QQmlEngine *engine, MainApplication *mainApp);
    void update() override;
    ~HomePage();

    void setCurrentForm(BaseForm *form);

    template <typename FormType, typename ...Args> requires IsForm<FormType>
    void switchForm(Args... args);

    template <typename ElementType, typename ...Args> requires IsPage<ElementType>
    BasePage* createElement(Args... args);

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
    BaseForm *curForm = nullptr;
    Models::Rooms rooms;
};

// extern template void homePage::switchPage<ListRoomsPage>();

#endif // HOME_PAGE_H
