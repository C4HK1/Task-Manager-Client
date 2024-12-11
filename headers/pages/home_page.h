#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include <QSignalMapper>
#include "base_page.h"
#include "base_form.h"
#include "base_message.h"
#include "models.h"
#include "network_manager.h"
#include "home_page_contents.h"
#include "main_application.h"
#include "navigation_service.h"

class HomePage : public BasePage {
    Q_OBJECT
public:
    MainApplication *mainApp;
    Kafka::Consumer *consumer;

    HomePage(QQmlEngine *engine, MainApplication *mainApp, const std::string &topic);
    ~HomePage();

    void update() override;
    void leave() override;

    //Message part
    void setCurrentMessage(BaseMessage *message);

    template <typename MessageType, typename ...Args> requires IsMessage<MessageType>
    void switchMessage(Args... args);

    //Form part
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

    void switchToInviteMessage(nlohmann::json message);

    void switchToAllTasks();
    void switchToReviewedTasks();
    void switchToAssignedTasks();

    void switchToAllInvites();
    void switchToReceivedInvites();
    void switchToSendedInvites();

    void switchBackward();
    void switchForward();

    void closeMessage();
    void closeForm();
    void closePage();
protected:
private:
    QQuickItem *workspace = nullptr;
    NavigationService *nav_service = nullptr;
    BaseForm *curForm = nullptr;
    BaseMessage *curMessage = nullptr;
    Models::Rooms rooms;
};

// extern template void homePage::switchPage<ListRoomsPage>();

#endif // HOME_PAGE_H
