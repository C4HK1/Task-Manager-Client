#include "home_page.h"
#include "main_application.h"

//Object part
HomePage::HomePage(QQmlEngine *engine, MainApplication *mainApp) :
        BasePage(engine, "qml/MainWorkspace.qml"),
        workspace(object->findChild<QQuickItem*>("workspace")),
        nav_service(new NavigationService(workspace, 20)),
        mainApp(mainApp) {
    static QList<std::string> switch_slots {
        "switchToWidgetRooms()", "switchToListRooms()", "switchToSettings()",
        "switchToProfile()", "switchToAllTasks()", "switchToReviewedTasks()", "switchToAssignedTasks()",
        "switchToLoggoutForm()", "switchToProfileDeleteForm()", "switchToTaskForm()",
        "switchToAllInvites()", "switchToReceivedInvites()", "switchToSendedInvites()",
        "switchBackward()", "switchForward()"
    };

    for (std::string &switch_slot : switch_slots) {
        connect(object, ("2" + switch_slot).c_str(), this, ("1" + switch_slot).c_str());
    }

    switchToWidgetRooms();
}

HomePage::~HomePage() {
    nav_service->deleteLater();
}

void HomePage::update() {}
void HomePage::leave() {}

//Elements management

//Form part
void HomePage::setCurrentForm(BaseForm *form){
    if (curForm != nullptr) {
        curForm->deleteLater();
    }

    curForm = form;

    if(curForm != nullptr) {
        connect(curForm->getObject(), SIGNAL(closeForm()), this, SLOT(closeForm()));
    }
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

void HomePage::switchBackward() { nav_service->switchBackward(); }
void HomePage::switchForward() { nav_service->switchForward(); }
