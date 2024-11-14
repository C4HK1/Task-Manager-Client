#include "home_page.h"
#include "main_application.h"

//Object part
HomePage::HomePage(QQmlEngine *engine, MainApplication *mainApp) :
        BasePage(engine, "qml/MainWorkspace.qml"),
        workspace(object->findChild<QQuickItem*>("workspace")),
        nav_service(new NavigationService(engine, workspace)),
        mainApp(mainApp) {
    static QList<std::string> switch_slots {
        "switchToWidgetRooms()", "switchToListRooms()", "switchToSettings()",
        "switchToProfile()", "switchToAllTasks()", "switchToReviewedTasks()", "switchToAssignedTasks()",
    };

    for (std::string &switch_slot: switch_slots) {
        connect(object, ("2" + switch_slot).c_str(), this, ("1" + switch_slot).c_str());
    }

    connect(this->getObject(), SIGNAL(switchToLoggoutForm()), this, SLOT(switchToLoggoutForm()));
    connect(this->getObject(), SIGNAL(switchToProfileDeleteForm()), this, SLOT(switchToProfileDeleteForm()));

    connect(this->getObject(), SIGNAL(switchToAllInvites()), this, SLOT(switchToAllInvites()));
    connect(this->getObject(), SIGNAL(switchToReceivedInvites()), this, SLOT(switchToReceivedInvites()));
    connect(this->getObject(), SIGNAL(switchToSendedInvites()), this, SLOT(switchToSendedInvites()));

    switchToWidgetRooms();
}

HomePage::~HomePage() {
}

void HomePage::update() {}

//Elements management

//Form part
void HomePage::setCurrentForm(BaseForm *form){
    if (curForm != nullptr) {
        curForm->deleteLater();
    }

    curForm = form;
}

template <typename FormType, typename ...Args> requires IsForm<FormType>
void HomePage::switchForm(Args... args) {
    setCurrentForm(new FormType(engine, this->getObject(), this, args...));
}

//Page part

template <typename ElementType, typename ...Args> requires IsPage<ElementType>
BasePage* HomePage::createElement(Args... args) {
    return new ElementType(engine, args...);
}

//Slots

//Form
void HomePage::closeForm() { setCurrentForm(nullptr); }
void HomePage::closePage() { /* setCurrentPage(nullptr); */ }

void HomePage::switchToLoggoutForm() { switchForm<LoggoutForm>(); }
void HomePage::switchToProfileDeleteForm() { switchForm<ProfileDeleteForm>(); }

//Page
void HomePage::switchToRoom(Models::Room room) { nav_service->switchTo(createElement<Room>(this, room)); }
void HomePage::switchToWidgetRooms() { nav_service->switchTo(createElement<WidgetRooms>(this)); }
void HomePage::switchToListRooms() { nav_service->switchTo(createElement<ListRooms>(this)); }
void HomePage::switchToSettings() { nav_service->switchTo(createElement<Settings>(this)); }
void HomePage::switchToRoomCreation() { nav_service->switchTo(createElement<RoomCreation>(this)); }
void HomePage::switchToProfile() { nav_service->switchTo(createElement<Profile>(this)); }

void HomePage::switchToAllTasks() { nav_service->switchTo(createElement<AllTasks>(this)); }
void HomePage::switchToReviewedTasks() { nav_service->switchTo(createElement<ReviewedTasks>(this)); }
void HomePage::switchToAssignedTasks() { nav_service->switchTo(createElement<AssignedTasks>(this)); }

void HomePage::switchToAllInvites() { nav_service->switchTo(createElement<AllInvites>(this)); }
void HomePage::switchToReceivedInvites() { nav_service->switchTo(createElement<ReceivedInvites>(this)); }
void HomePage::switchToSendedInvites() { nav_service->switchTo(createElement<SendedInvites>(this)); }

