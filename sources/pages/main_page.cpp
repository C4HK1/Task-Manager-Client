#include "main_page.h"

MainPage::MainPage(QQmlEngine *engine, QQuickItem *container) :
        BasePage(engine, container, "qml/MainWorkspace.qml"),
        workspace(object->findChild<QQuickItem*>("workspace")) {
    static QList<std::string> switch_slots {
        "switchToWidgetRooms()", "switchToListRooms()", "switchToSettings()",
        "switchToProfile()", "switchToTasks()"
    };

    for (std::string &ss: switch_slots) {
        connect(object, ("2" + ss).c_str(), this, ("1" + ss).c_str());
    }

    connect(this->getObject(), SIGNAL(loggout()), this, SLOT(loggout()));
    connect(this->getObject(), SIGNAL(deleteProfile()), this, SLOT(deleteProfile()));
    connect(netManager, &NetworkManager::finishDeleteProfileResponseHandling, this, &MainPage::finishDeleteProfile);

    switchToWidgetRooms();
}

void MainPage::deleteProfile()
{
    netManager->sendDeleteProfileRequest();
}

void MainPage::finishDeleteProfile(ServerStatus serverStatus)
{
    if (!serverStatus.status) {
        std::remove("data/authentication_key.organizer");
        emit switchToLogginingPage();
    } else {
        qInfo() << "error profile deleting with status: " << serverStatus.status;
    }
}

void MainPage::loggout()
{
    std::remove("data/authentication_key.organizer");
    emit switchToLogginingPage();
}

void MainPage::setCurrentPage(BasePage *page){
    if (curPage != nullptr) {
        curPage->deleteLater();
    }

    curPage = page;
}

void MainPage::setCurrentForm(BasePage *form){
    if (curForm != nullptr) {
        curForm->deleteLater();
    }

    curForm = form;
}

template <typename FormType, typename ...Args> requires IsPage<FormType>
void MainPage::switchForm(Args... args) {
    qInfo() << this->curPage->getObject();
    setCurrentForm(new FormType(engine, this->curPage->getObject(), args...));
}

void MainPage::closeForm() {
    setCurrentForm(nullptr);
}

template <typename PageType, typename ...Args> requires IsPage<PageType>
void MainPage::switchPage(Args... args) {
    setCurrentPage(new PageType(engine, workspace, args...));
}

void MainPage::switchToRoom(Room room) {
    switchPage<RoomPage>(room);
    connect(dynamic_cast<RoomPage *>(this->curPage), &RoomPage::switchToTaskCreation, this, &MainPage::switchToTaskCreation);
}
void MainPage::switchToWidgetRooms() { switchPage<WidgetRoomsPage>(this); }
void MainPage::switchToListRooms() { switchPage<ListRoomsPage>(this); }
void MainPage::switchToSettings() { switchPage<SettingsPage>(); }
void MainPage::switchToRoomCreation() { switchPage<RoomCreationPage>(this); }
void MainPage::switchToProfile() { switchPage<ProfilePage>(); }
void MainPage::switchToTasks() { switchPage<TasksPage>(this); }

void MainPage::switchToTaskCreation() {
    switchForm<TaskCreationPage>();
    connect(dynamic_cast<TaskCreationPage *>(this->curForm), &TaskCreationPage::closeTaskCreatiornForm, this, &MainPage::closeForm);
}

