#include <nlohmann/json.hpp>

#include "profile_delete_form.h"
#include "main_page.h"

ProfileDeleteForm::ProfileDeleteForm(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage) :
        BasePage(engine, container, "qml/ProfileDelete.qml"),
        mainPage(mainPage) {
    connect(this->getObject(), SIGNAL(profileDelete()), this, SLOT(profileDelete()));
    connect(this->getObject(), SIGNAL(closeProfileDeleteForm()), this, SLOT(closeProfileDeleteForm()));

    connect(this->netManager, &NetworkManager::finishDeleteProfileResponseHandling, this, &ProfileDeleteForm::finishProfileDelete);
}

void ProfileDeleteForm::profileDelete() {
    this->netManager->sendDeleteProfileRequest();
}

void ProfileDeleteForm::closeProfileDeleteForm() {
    this->mainPage->closeForm();
}

void ProfileDeleteForm::finishProfileDelete(ServerStatus serverStatus) {
    if (!serverStatus.status) {
        this->mainPage->mainApp->switchToLogginingPage();
    } else {
        qInfo() << "error profile deleting with status: " << serverStatus.status;
    }
}

ProfileDeleteForm::~ProfileDeleteForm() {}
