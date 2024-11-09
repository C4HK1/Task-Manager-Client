#include "home_page.h"
#include "main_application.h"

//Object part
HomePage::HomePage(QQmlEngine *engine, QQuickItem *container, MainApplication *mainApp) :
        BaseElement(engine, container, "qml/MainWorkspace.qml"),
        workspace(object->findChild<QQuickItem*>("workspace")),
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
void HomePage::setCurrentPage(BaseElement *element){
    if (curWorkspaceElement != nullptr) {
        curWorkspaceElement->deleteLater();
    }

    curWorkspaceElement = element;
}

template <typename PageType, typename ...Args> requires IsElement<PageType>
void HomePage::switchPage(Args... args) {
    setCurrentPage(new PageType(engine, workspace, this, args...));
}


//Slots

//Form
void HomePage::closeForm() { setCurrentForm(nullptr); }
void HomePage::closePage() { setCurrentPage(nullptr); }

void HomePage::switchToLoggoutForm() { switchForm<LoggoutForm>(); }
void HomePage::switchToProfileDeleteForm() { switchForm<ProfileDeleteForm>(); }

//Page
void HomePage::switchToRoom(Models::Room room) { switchPage<Room>(room); }
void HomePage::switchToWidgetRooms() { switchPage<WidgetRooms>(); }
void HomePage::switchToListRooms() { switchPage<ListRooms>(); }
void HomePage::switchToSettings() { switchPage<Settings>(); }
void HomePage::switchToRoomCreation() { switchPage<RoomCreation>(); }
void HomePage::switchToProfile() { switchPage<Profile>(); }

void HomePage::switchToAllTasks() { switchPage<AllTasks>(); }
void HomePage::switchToReviewedTasks() { switchPage<ReviewedTasks>(); }
void HomePage::switchToAssignedTasks() { switchPage<AssignedTasks>(); }

void HomePage::switchToAllInvites() { switchPage<AllInvites>(); }
void HomePage::switchToReceivedInvites() { switchPage<ReceivedInvites>(); }
void HomePage::switchToSendedInvites() { switchPage<SendedInvites>(); }

