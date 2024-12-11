#include <nlohmann/json.hpp>

#include "profile_delete_form.h"
#include "home_page.h"

//Object part
ProfileDeleteForm::ProfileDeleteForm(QQmlEngine *engine, QQuickItem *parent, HomePage *homePage) :
    BaseForm(engine, parent, "qml/ProfileDelete.qml"),
    homePage(homePage) {
    connect(this->getObject(), SIGNAL(profileDelete()), this, SLOT(profileDelete()));
    connect(this->getObject(), SIGNAL(closeProfileDeleteForm()), this, SLOT(closeProfileDeleteForm()));

    connect(this->netManager, &NetworkManager::finishDeleteProfileResponseHandling, this, &ProfileDeleteForm::finishProfileDelete);
}

ProfileDeleteForm::~ProfileDeleteForm() {
}


//Slots
void ProfileDeleteForm::profileDelete() {
    this->netManager->sendDeleteProfileRequest();
}

void ProfileDeleteForm::closeProfileDeleteForm() {
    this->homePage->closeForm();
}

void ProfileDeleteForm::finishProfileDelete(Models::ServerStatus serverStatus) {
    if (!serverStatus.status) {
        this->homePage->mainApp->switchToLogginingPage();
    } else {
        qInfo() << "error profile deleting with status: " << serverStatus.status;
    }
}
