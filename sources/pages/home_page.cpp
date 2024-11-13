#include "home_page.h"
#include "main_application.h"

//Object part
HomePage::HomePage(QQmlEngine *engine, QQuickItem *container, MainApplication *mainApp) :
        BaseElement(engine, "qml/MainWorkspace.qml"),
        workspace(object->findChild<QQuickItem*>("workspace")),
        nav_service(engine, workspace),
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


//Elements management

//Form part
void HomePage::setCurrentForm(BaseElement *form){
    if (curForm != nullptr) {
        curForm->deleteLater();
    }

    curForm = form;
}

template <typename FormType, typename ...Args> requires IsElement<FormType>
void HomePage::switchForm(Args... args) {
    setCurrentForm(new FormType(engine, this->getObject(), this, args...));
}

//Page part


//Slots

//Form
void HomePage::closeForm() { setCurrentForm(nullptr); }
void HomePage::closePage() { /* setCurrentPage(nullptr); */ }

void HomePage::switchToLoggoutForm() { switchForm<LoggoutForm>(); }
void HomePage::switchToProfileDeleteForm() { switchForm<ProfileDeleteForm>(); }

//Page
void HomePage::switchToRoom(Models::Room room) { nav_service.switchTo<Room>(room); }
void HomePage::switchToWidgetRooms() { nav_service.switchTo<WidgetRooms>(); }
void HomePage::switchToListRooms() { nav_service.switchTo<ListRooms>(); }
void HomePage::switchToSettings() { nav_service.switchTo<Settings>(); }
void HomePage::switchToRoomCreation() { nav_service.switchTo<RoomCreation>(); }
void HomePage::switchToProfile() { nav_service.switchTo<Profile>(); }

void HomePage::switchToAllTasks() { nav_service.switchTo<AllTasks>(); }
void HomePage::switchToReviewedTasks() { nav_service.switchTo<ReviewedTasks>(); }
void HomePage::switchToAssignedTasks() { nav_service.switchTo<AssignedTasks>(); }

void HomePage::switchToAllInvites() { nav_service.switchTo<AllInvites>(); }
void HomePage::switchToReceivedInvites() { nav_service.switchTo<ReceivedInvites>(); }
void HomePage::switchToSendedInvites() { nav_service.switchTo<SendedInvites>(); }

