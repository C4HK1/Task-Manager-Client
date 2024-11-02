#include "main_page.h"
#include "main_application.h"

MainPage::MainPage(QQmlEngine *engine, QQuickItem *container, MainApplication *mainApp) :
        BasePage(engine, container, "qml/MainWorkspace.qml"),
        workspace(object->findChild<QQuickItem*>("workspace")),
        mainApp(mainApp) {
    static QList<std::string> switch_slots {
        "switchToWidgetRoomsPage()", "switchToListRoomsPage()", "switchToSettingsPage()",
        "switchToProfilePage()", "switchToTasksPage()"
    };

    for (std::string &switch_slot: switch_slots) {
        connect(object, ("2" + switch_slot).c_str(), this, ("1" + switch_slot).c_str());
    }

    connect(this->getObject(), SIGNAL(switchToLoggoutForm()), this, SLOT(switchToLoggoutForm()));
    connect(this->getObject(), SIGNAL(switchToProfileDeleteForm()), this, SLOT(switchToProfileDeleteForm()));

    switchToWidgetRoomsPage();
}

//Elements management

//Form part
void MainPage::setCurrentForm(BasePage *form){
    if (curForm != nullptr) {
        curForm->deleteLater();
    }

    curForm = form;
}

template <typename FormType, typename ...Args> requires IsPage<FormType>
void MainPage::switchForm(Args... args) {
    setCurrentForm(new FormType(engine, this->getObject(), this, args...));
}

//Page part
void MainPage::setCurrentPage(BasePage *page){
    if (curPage != nullptr) {
        curPage->deleteLater();
    }

    curPage = page;
}

template <typename PageType, typename ...Args> requires IsPage<PageType>
void MainPage::switchPage(Args... args) {
    setCurrentPage(new PageType(engine, workspace, this, args...));
}


//Slots

// void MainPage::deleteProfile()
// {
//     netManager->sendDeleteProfileRequest();
// }

//Switchers

//Form
void MainPage::closeForm() { setCurrentForm(nullptr); }

void MainPage::switchToLoggoutForm() { switchForm<LoggoutForm>(); }
void MainPage::switchToProfileDeleteForm() { switchForm<ProfileDeleteForm>(); }

//Page
void MainPage::switchToRoomPage(Room room) { switchPage<RoomPage>(room); }
void MainPage::switchToWidgetRoomsPage() { switchPage<WidgetRoomsPage>(); }
void MainPage::switchToListRoomsPage() { switchPage<ListRoomsPage>(); }
void MainPage::switchToSettingsPage() { switchPage<SettingsPage>(); }
void MainPage::switchToRoomCreationPage() { switchPage<RoomCreationPage>(); }
void MainPage::switchToProfilePage() { switchPage<ProfilePage>(); }
void MainPage::switchToTasksPage() { switchPage<TasksPage>(); }
